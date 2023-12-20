From a structure perspective, a commonjs module is a reusable piece of Javascript code which exports specific objects made available to any dependent code.
At a high-level they basically contain 2 primary parts: a free variable named `exports` which contains the objects a module wishes to make available to other modules and a `require` function that modules can use to import the exports of other modules.

Module structure:

```javascript
// package/lib is a dependency we require
var lib = require("package/lib");

// some behaviour for our module
function foo() {
  lib.log("hello world!");
}

// some side effects the module has
function init() {
  writeFile();
}

init();

// export (expose) foo to other modules
exports.foo = foo;
```
