---
title: "Preview Server System Design"
---

# Preview server

The main responsibility of preview server is to response to the application frontend resource requests.

And do the minimal work to transform the source code to a running JS code for browser.

An overview of service dependencies

overview of services

## Core Modules

- Source Management
- Optimizer
- Preview Server
- Vite
    - base config
    - runtime config
    - plugins
- Shared Deps

### Source Management

The source code management have these functionalities:

1. Generate remoteEntry.js and sandbox wrapper

The remoteEntry is the bridge between our frontend systems, eg. the main App will request app’s remoteEntry to render its content. For Preview, its play the same role as normal bundled applciations, it will be uploaded into a static resource storage service.

Exp.

```jsx
const entries = {
        './Entry': ()=>import('https://service-pre.xxx.com/sandbox/resource/4778028619903289062/pc/src/app-sandbox-wrapper.tsx?h=1678950480221').then((mod)=>()=>mod)
    };
    window['xxx'] = {
        init() {},
        get(name) {
            return entries[name]()
        }
    };
```

The sandbox wrapper is an extra file for display some Preview specifical content, like

```jsx
function SandboxWrapper(props: any) {
  return (
    <>
      <Alert
        banner
        message={
          <LoopBanner pauseOnHover gradient={false}>
          此应用运行在沙箱环境中，页面性能可能会下降！
          </LoopBanner>
        }
        type="warning"
        closable
      />
      <React.Suspense fallback={<Skeleton active />}>
        <Entry {...props} />
      </React.Suspense>
    </>
  );
}
```

1. remote resource

If we want the preview service to be stateless, we have to ship the state to the outside, the remote resource module is used to transfer and retrieve sources code (the generated code) from the external storage(Redis). The resource was stored by key `${appId}-${platform}`, each key has a corresponding version key which is used to check the consistency between resources in runtime and external, if the resource requests come in, we will first check whether the version key matched, so we do not have to fetch the resource from external for every request.

So there has 3 layers of cache for our resources

![../assets/Untitled](../assets/123.png)

The process of preview server to handle resource requests be like:

![../assets/Untitled](../assets/456.png)

1. Lifecycle 

Based on the NodeJS core concept: [Don't block the event loop]([https://nodejs.org/en/docs/guides/dont-block-the-event-loop/](https://nodejs.org/en/docs/guides/dont-block-the-event-loop/)), the process of the source code generation should be off-loaded.

But this may cause race condition on same source files when parallel requests come with same APP id.

Imagine if the main thread of NodeJS processing on 2 same requests with different app state, the generation of the source code will be executed concurrently between the 2 function stacks, since they both operate on the same source files, the final generated app files may have inconsistent code.

Some defense mechanism must be taken to prevent such situation, it ensures each request update the file with its own app state.

Use Redis lock ([https://redis.io/commands/setnx/#design-pattern-locking-with-setnx](https://redis.io/commands/setnx/#design-pattern-locking-with-setnx)) and a Redis storage can solve this dilemma,

```

requestHandler() {

try {

if (redis.lock.acquire(appID)) {

const status = redis.get(appID)

if (status === 1) return; // collision detected

// generation

redis.set(appID, 1); // pending the process

generateApp();

redis.del(appID) // the process done

}

} finally {

redis.lock.release(appID)

}

}

```

### 

The status was managed by UDC service previously, since we bypassed it now, we have to implement it too. We still can use Redis to store the status of the app generation, like the code above.

### Optimizer

The optimizer is coming from Vite internal module, the main job it does is optimizing on dependencies, and this has 2 stages:

1. pre-bundling before server start (the dependencies defined in the shared-deps)
2. discovery of new dependencies when server running (the customer dependencies)

Since we're using cluster mode, we can run stage 1 optimizing at the master process, this also play a pre-check function for our dependencies, after the pre-bundling, each slave process starts, and the vite server will not run optimizing redundantly since there is no changes for dependency.

For the stage 2 optimizing, the situation becomes a little complicated, the discovery of new dependency can only happen when server start process the resource requests, so there have a case we have to handle:

1. How to optimize on new dependencies since not all server instances have installed the new dependency, and it's not efficient to install the dependency at the timing when requests come in.
2. If there still has dependencies that not declare in the shared-deps/package.json, how to found it? If the same dependency was discovered by different processes or instances since they know nothing about each other, how to prevent resource waste on redundant optimizing and inconsistency (2 different versions of instance maybe exists in same time, the optimizing result may differ)
3. This behavior was controlled by vite, and there is no public API to control it, modify on source code or write an optimizer plugin from start?

Thankfully, the vite use a `WeakMap` to store the optimizer, thus we can expose the internal optimizer by hacking the prototype of the `WeakMap` set method, and rewrite its functions.

To solve the first case, we can install customer dependencies when the source code was generated, since the customer dependencies must declare in the `customPackage.json`, then optimizing on these dependencies, publish the optimized files to OSS, also we need to upload the metadata to the Redis which can be used to check is the module needs interop or not. When the new dep was discovered, we will first check the metadata info on the Redis, if exists we will use the metadata directly and rewrite the import statement to redirect to OSS address

For the second one, we can add a distributed lock on the optimizer, and publish the optimized dep to the OSS, furthermore, we should check on OSS, and write these undeclared deps into config

![../assets/Untitled](../assets/789.png)

### Version 2 Optimizer

The source code and dependencies can generate independently, since we can not control the time of the dependencies generation, we want it is non-block for source code generation.

Use commonjs-analysis to avoid interop wrapper when cjs translated to esm

The application’s dependencies vary, even on same dependencies they may dependends on different version, and we do not want the app need to be re-generated for every dependencies change(unless its has breaking change)

There have 2 different way to handle this:

1. Fixed version

/lib/esm/xxx@version.mjs

redis:

location /lib/esm {

try xxx@version.mjs

fallback xxx.mjs // since the version may not exists due to a publish error for xxx

}

cons: need re-depoly

pros: 

1. Always lts (current implementation)

/lib/esm/xxx.@lts.mjs

OSS:

xxx.1.0.1.mjs

xxx.1.0.2.mjs ← xxx.lts.mjs // replace the lts file for every release

cons: do not support multi-version

1. Follow Application’s data

/app1/lib/esm/xxx.mjs

worker.js or gateway:

if isLib(request.url):

const depName = extractDepNameFromReuest(request)

const appId = extractAppIdFromReuest(request)

const version = await getDepData(appId, depName )

request.url = append(request.url, version)

### Preview Server

It serves resources requests from the clients, interact with vite internal state like module graph and optimizer.

### Vite

The vite’s dev server core concepte is lazy loading and laverage with es modules.

## API

- create
- status

## The plugins

1. Memorized loader

Since we treat the file as a state and shipped these state to Redis, we have to tell vite to found the file from elsewhere, the memorized loader will help vite resolve and load the file from memory(which fetched from Redis)

## The performance bottleneck

Cpu: We use thread pool to run tasks of the udc-code-engine and the dependencies update, althought the udc-code-engine is not a cpu-intensive task(io-intensive instead), we still need to utilize the multi-core ablebility for our udc-sandbox server.

Memory: At the runtime, massive concurrent http requets will issued by browser, if we can eliminate the sandbox, we could pre-fetch the resources and leverage with the browser caches. For cache first stretage(do not need re-transpile source code), the server will store lots of transpiled code, if we do not have a well planned load balaner, the memory can not be controlled very well

## The sandbox

In the main/children mode, the applications run in the different tabs, some state is maintained by a local variable in the esmodule, if 2 tabs import the same esmodule that contains state, the local variable will be overwritten by the last one, the browser will treat the 2 imports as the same module since their ImportSpecifier are the same, we could append a sandbox id to the ImportSpecifier to make the same esmodule become 2 different ones, to achieve this we have to append the sandbox id to every requests that initialized by the tabs(the requests may hit to different runtime instances), we use a global variable `**sandbox_load_count**` to count on the tab opening, and the preview server will append every resource a sandbox ID includes the dependency modules. So the resource request will become to:

`/app-runtime/preview/resource/123/pc/src/pages/index/costomPage.tsx?h=1670650504301&sandbox=1`

## The Vite

The Vite itself is a development tool, it holds many local states for performance perspective, such as optimizing metadata (the optimized dependencies' info), module graph (the transformed source code modules), even the file system itself is a state for our runtime service(the native resource load approach). The preview need to high available, which means it need horizontal scaling, there has 2 ways to achieve it:

1. A reverse proxy

The requests to the preview server is self-contained, it has the information on the HTTP request, e.g. the app ID on the HTTP path `/udc-app-runtime/preview/resource/431306586676806014/pc/src/utils/event-bus/index.ts`,

we could run a simple algorithm to dispatch the requests to the same preview server if they have the same app ID:

`SERVER_ID = hash("431306586676806014") mod len(preview servers)`

We could also inject a SERVERID in the response cookie, when the client comes again with the cookie "SERVERID=A", the proxy will know that it must be forwarded to server A. The cookie will be removed so that the server does not see it.

2. Stateless server(current implementation)

The state in the Vite could be eliminated, if we can ship them to the external system like Redis or other database. Compare to the first solution, a stateless server will suffer on the consistency, because we have to synchronize on the external states, but it also has a better partition tolerance than the first approach, the consistency is very important to the preview server, but the stateless way is more controllable, we could run a long term optimization on it.

## System integration

The output of preview is nothing but esmodules, import these preview module would be easy, the System can load the preview resource without any **cognitive load**.

[Distributed ESM](https://www.notion.so/Distributed-ESM-0a5a213c9a114ab4ac292144b7b25c52?pvs=21)