---
title: "Ternary Operator Limitations"
---

function tenaryGen(count) {
  let operations = 'x === y ? 1 : 0'
  for (let i = 0; i < count; i++) {
    operations = 'x === y ? ' + operations + ': 0'
  }

  return operations
}
eval(tenaryGen(1352)) // 
eval(tenaryGen(1353)) // Uncaught RangeError: Maximum call stack size exceeded


[this exception usually occurs when mifier want to ](https://github.com/terser/terser/issues/1432)
https://bugs.chromium.org/p/v8/issues/detail?id=13887&q=ternary&can=1