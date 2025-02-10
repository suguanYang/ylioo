---
title: "ESM and CommonJS Interoperability"
---

The ESM and CJS are totally different things.

The CJS can not import ESM due to top level await

The ESM can import CJS through interop

```
import _ from 'lodash'

const { get }  = _
```

or with out-of-order excution

The transformation of ESM and CJS

when ESM transform to CJS the default export of ESM will transform to a named export in CJS

```
export default 1;


// transform
exports.default = 1; // not tmodule.exports = 1
Object.defineProperty(exports, '__esModule', { value: true });
```

when CJS transform to ESM, the usual way is to wrap the whole CJS module in a function and the transfomed
ESM code will export default of the return value of that warpper, this preserved the semantic of CJS: the
exports are determined when code excution.

```by esbuild
var __getOwnPropNames = Object.getOwnPropertyNames;
var __commonJS = (cb, mod) => function __require() {
  return mod || (0, cb[__getOwnPropNames(cb)[0]])((mod = { exports: {} }).exports, mod), mod.exports;
};
var require_stdin = __commonJS({
  "<stdin>"(exports, module) {
    const A = 1;
    const B = 2;
    module.exports = {
      A,
      B,
      default: 1
    };
  }
});
export default require_stdin();


```

But this will force the invoker to import the default value of
the cjs-esm, and deconstruct the named export from the default value, a work around to this is to wrap the cjs-esm
with CJS's named export to ESM named export:

```
// the wrapper
 private async wrapESM(cjsModule) {
    await init();

    const raw = await readFile(cjsModule, "utf-8");
    const ast = parse(raw);

    const namedExports = ast.exports;

    let wrapESMContent = `
import * as __module from "${cjsModule}";
const { default: __default, ...__rest } = __module;
export default (__default !== undefined ? __default : __rest);
      `;

    if (namedExports && namedExports.length > 0) {
      wrapESMContent += `export const { ${namedExports
        .filter((name) => name !== "default")
        .join(",")} } = __default ?? __module;`;    // if the default is present, all the named export will bind on it
    }

    const wrapESMPath = path.dirname(cjsModule) + "/index.mjs";
    await writeFile(wrapESMPath, wrapESMContent, "utf-8");

    return wrapESMPath;
  }
```
