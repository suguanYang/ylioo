```javascript
function OrdinaryToPrimitive(O: object, hint: 'string' | 'number') {
  let methodNames;
  if (hint === 'string') {
    methodNames = ['toString', 'valueOf'];
  } else {
    methodNames = ['valueOf', 'toString'];
  }
  for (let name of methodNames) {
    let method = O[name];
    if (IsCallable(method)) {
      let result = method.call(O);
      if (TypeOf(result) !== 'object') {
        return result;
      }
    }
  }
  throw new TypeError();
}

function ToPrimitive(input: any, hint: 'string'|'number'|'default' = 'default') {
    if (TypeOf(input) === 'object') {
      let exoticToPrim = input[Symbol.toPrimitive]; // (A)
      if (exoticToPrim !== undefined) {
        let result = exoticToPrim.call(input, hint);
        if (TypeOf(result) !== 'object') {
          return result;
        }
        throw new TypeError();
      }
      if (hint === 'default') {
        hint = 'number';
      }
      return OrdinaryToPrimitive(input, hint);
    } else {
      // input is already primitive
      return input;
    }
  }
```