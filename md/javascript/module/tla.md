---
title: "Top Level Await Behavior and Execution Order"
---

TLA will not block the excuiton order of sibling modules.
```javascript
const timeout = new Promise((resolve) => setTimeout(resolve, 1000));
await timeout;
import "./tla-inner-siblingA.ts";
export default 1;
```

for the above code, the excution order still be post-order: tla-inner-siblingA.ts -> tla.ts.

If the module import a TLA module A, the module A's excution order wil follow the async excution model
```javascript
import A from "./tla-inner.ts";
import "./tla-inner-siblingA.ts";
export default 1;
```

for the above code, the excution order will be: tla-inner.ts(before await) -> tla-inner-siblingA.ts -> tla-inner.ts(after await) -> tla.ts.


but if we change the code to this
```javascript
const inner = await import("./tla-inner.ts");
import "./tla-inner-siblingA.ts";
export default 1;
```
the excution order will be same as the previous one.

thus we can conclude that the excution of the imported module(by import statement) will follow the pre-order regardless of the TLA.
TLA occurs during the execution phase of the module graph. At this point all resources have already been fetched and linked. There is no risk of blocking fetching resources.


## Why TLA?
Without top-level await, JavaScript developers often used async immediately-invoked function expressions just to get access to await. 
Unfortunately, this pattern results in less determinism of graph execution and static analyzability of applications. For these reasons, 
the lack of top-level await was viewed as a higher risk than the hazards introduced with the feature.