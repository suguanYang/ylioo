---
title: "ESM and CommonJS under bundler"
---

The transformation of ESM and CJS

when ESM transform to CJS the default export of ESM will transform to a named export in CJS

```
export default 1;


// transform
exports.default = 1; // not module.exports = 1
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

## Require

when cjs `require` is used, mostly in some libary that declared to support both node and browser, they often achive this by

```
  <!-- using browser api -->
  if (typeof window !== "undefined" && window.api) {
        return window.api();
  }
  else if (typeof require === "function") {
      return require("xxx")();
  }
```
this is troublesome when a bundler like webpack try to bundle on this module to browser. it will see the `require` is used, it will try bundle the required module to output, but that module is not browser compatible. some library wil try to bypass webpack's require behavior by using `__non_webpack_require__` to avoid the bundler to bundle the required module

But require and import are totally different things, require runs at runtime, for js perspecitve its just a fucntion call, while import in specification is a declaration, its just a
pure semantic and static analysisble top level structure, also the dynamic import expression is not equivalent to require, it returns a promise.

### TLA

furthermore, when TLA is used, cjs and module are become more imcompatible, asume module A is a module that use TLA,
whats the result of a `require(esm)`? nodejs still works on this, but how bundler deal with it? webpack support a simmilar
concepte like TLA called async modules, it transforms the async module imports like this:
```
async module() {
  const esm = await webpack_require('async_esm'); 

  function fn() {
    // use module as is a sync module
    return esm.default;
  }
}
```
but this has color problem, all modules that involved this module alone the path will transform to async modules too, until there is
a `require()` call on that path, webpack will keep the async module as is
 

### Live binding
CJS exports are mutable and totally in runtime, what you get from require() is just a normal object reference
that can be mutated at any time, you can change the value of `exports.default` or `exports.foo` after the module is loaded, and the change will be reflected in all places that require that module. In contrast, ESM exports are immutable, once an ESM module is loaded, its exports are fixed and cannot be changed.

But ESM has "live binding", the imported member is a live reference to the exported member, if the exported member is changed, the imported member will reflect that change. so import statment is not simply a const declaration, but how we can achive this in the bundler?

1. The Module as a Singleton Namespace Object 
the bundler creates a live link or a proxy to the property on the module's namespace object.
So, whenever you use the imported member in your code, you are implicitly calling the getter which fetches the current value from the original module's scope. You are, always accessing it "through that Object," even if the syntax makes it look like a local variable. This is precisely how live binding is preserved.

```
import { setA, a } from "./a.js";

console.log(a); // 1
setA();
console.log(a); // 2

export default 1;
```

2. Static linking with Inline Scope Hoisting
The bundler can also use scope hoisting to ensure that the imported members are always accessed directly from the importing modules scope as a variable.
```
var __getOwnPropNames = Object.getOwnPropertyNames;
var __esm = (fn, res) => function() {
	return fn && (res = (0, fn[__getOwnPropNames(fn)[0]])(fn = 0)), res;
};

//#endregion
//#region a.js
var a, setA;
var init_a = __esm({ "a.js"() {
	a = 1;
	setA = () => {
		a = 2;
	};
} });

//#endregion
//#region index.js
var index_default;
var init_index = __esm({ "index.js"() {
	init_a();
	console.log(a);
	setA();
	console.log(a);
	index_default = 1;
} });

//#endregion
init_index();
```
this can gain better performance since bare-name lookups are faster than property accesses


## Reference
https://github.com/evanw/esbuild/issues/946
https://joyeecheung.github.io/blog/2024/03/18/require-esm-in-node-js/
https://devongovett.me/blog/scope-hoisting.html