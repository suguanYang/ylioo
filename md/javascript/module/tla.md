---
title: "Top Level Await Behavior and Execution Order"
---

From the spec says: execution of module bodies starts with the deepest imports, in the order that the import statements for them are reached.
```javascript
// tla.ts
const timeout = new Promise((resolve) => setTimeout(resolve, 1000));
await timeout;
import "./tla-inner-siblingA.ts";
export default 1;
```

```javascript
// tla-inner-siblingA.ts
export default 1;
```

for the above code, the excution order still be post-order: tla-inner-siblingA.ts -> tla.ts.

If the module tla import tla-inner, the module excution order wil follow the async excution model(for the same level modules)
```javascript
// tla.ts
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

thus we can conclude that the initialization of the imported module(by import statement) will follow the post-order(DFS) regardless of the TLA.
TLA occurs during the execution phase of the module graph. At this point all resources have already been fetched and linked. There is no risk of blocking fetching resources.
