---
title: JS Performance
---

# Writing High-Performance JavaScript for V8

This guide provides actionable principles and practical examples to help write JavaScript code that performs optimally with the V8 engine.

## Table of Contents

1. [Object Shape and Memory Layout](#object-shape-and-memory-layout)
2. [Efficient Array Handling](#efficient-array-handling)
3. [Garbage Collection Friendliness](#garbage-collection-friendliness)
4. [Leveraging the JIT Compiler](#leveraging-the-jit-compiler)
5. [Asynchronous Operations](#asynchronous-operations)
6. [String and RegExp Optimizations](#string-and-regexp-optimizations)
7. [General Best Practices](#general-best-practices)

---

## Object Shape and Memory Layout

V8 uses "hidden classes" (or "shapes") to optimize property access. Objects with the same hidden class can be processed by the same optimized machine code.

### Initialize object properties consistently and in the same order

**Why:** This allows V8 to reuse hidden classes. Inconsistent initialization forces V8 to create new hidden classes, slowing down property access and potentially leading to deoptimizations.

#### ❌ Less Ideal Example
```javascript
// Inconsistent initialization
const obj1 = { name: "Alice" };
obj1.age = 30;

const obj2 = { age: 25 };
obj2.name = "Bob";
obj2.city = "New York";
```
**Issue:** `obj1` and `obj2` will likely have different hidden classes due to the order of property assignment.

#### ✅ More Ideal Example
```javascript
function createPerson(name, age, city) {
  // Consistent order and all properties initialized
  return {
    name: name,
    age: age,
    city: city
  };
}

const person1 = createPerson("Alice", 30, "London");
const person2 = createPerson("Bob", 25, "New York");
```
**Benefit:** Both objects share the same hidden class, enabling optimization reuse.

### Avoid adding or deleting properties after object creation

**Why:** Modifying an object's structure after creation forces V8 to transition to a new hidden class, which is costly. Deleting properties can move an object into slower "dictionary mode".

#### ❌ Less Ideal Example
```javascript
const user = { id: 1, name: "Charlie" };
// ... some time later
user.email = "charlie@example.com"; // Property added
delete user.name; // Property deleted
```

#### ✅ More Ideal Example
```javascript
// Initialize all expected properties, using null/undefined if not yet available
function createUser(id, name, email = null) {
  return {
    id: id,
    name: name,
    email: email,
    status: 'active'
  };
}

const user1 = createUser(1, "Charlie", "charlie@example.com");
// If name needs to be "removed", set it to null instead
const user2 = createUser(2, null, "dave@example.com");
```

### Keep property types consistent

**Why:** V8 optimizes operations based on observed property types. Type changes can cause deoptimization and force re-optimization.

#### ❌ Less Ideal Example
```javascript
let item = { price: 100 };
console.log(item.price * 2); // Optimized for 'price' as a number

item.price = "Not available"; // Type change causes deoptimization
console.log(item.price.toUpperCase());
```

#### ✅ More Ideal Example
```javascript
let item = { price: 100, status: "available" };
console.log(item.price * 2);

if (item.status === "available") {
    // Process normally
} else {
    item.price = 0; // Keep 'price' as a number
    item.status = "unavailable";
    console.log("Item is " + item.status);
}
```

---

### Bonus:

1. Do not use rest operator to copy objects, use Object.create instead.
```javascript
const largeObj = { ... };
const copiedObj = { ...largeObj };
``` 
better:
```javascript
const largeObj = { ... };
const copiedObj = Object.create(largeObj);
```

Why?
The Object.create will create a new object, and set the largeObj as the prototype of the new object, this will not cause a lot of memory allocation and copy operations, works like copy-on-write.

2. Avoid use rest operator to merge large objects

## Efficient Array Handling

V8 highly optimizes array operations, especially for arrays with consistent element types.

### Prefer "packed" arrays and consistent element kinds

**Why:** 
- **Packed arrays:** Arrays without holes allow faster element access than "holey" arrays
- **Consistent element kinds:** V8 tracks element types (SMI_ONLY_ELEMENTS, DOUBLE_ELEMENTS, etc.)

#### ❌ Less Ideal Example
```javascript
const mixedArray = [1, 2, /* hole */ , 4]; // Holey array
mixedArray.push(5.5); // Transitions to DOUBLE_ELEMENTS
mixedArray.push("hello"); // Transitions to general ELEMENTS
```

#### ✅ More Ideal Example
```javascript
// Packed array of small integers (SMI_ONLY_ELEMENTS)
const smis = [10, 20, 30, 40, 50];

// Packed array of doubles (DOUBLE_ELEMENTS)
const doubles = [1.1, 2.2, 3.3, 4.4, 5.5];

// Use placeholders instead of holes
const items = [getItem(0), null, getItem(2)];
```

### Use TypedArrays for raw binary data or large numeric arrays

**Why:** TypedArrays store data in contiguous memory without JavaScript object overhead per element, making them more memory-efficient and faster for large numeric operations.

#### ❌ Less Ideal Example
```javascript
const lotsOfNumbers = [];
for (let i = 0; i < 1000000; i++) {
  lotsOfNumbers.push(i * 0.5); // Each number is a heap-allocated JS object
}
```

#### ✅ More Ideal Example
```javascript
const count = 1000000;
const typedNumbers = new Float32Array(count);
for (let i = 0; i < count; i++) {
  typedNumbers[i] = i * 0.5; // Direct numeric storage
}
```

---

## Garbage Collection Friendliness

Write code that reduces GC pauses and memory pressure.

### Minimize object churn in hot functions

**Why:** Excessive object creation/destruction can lead to frequent garbage collection, impacting performance.

#### ❌ Less Ideal Example
```javascript
function sumPoints(points) {
  let total = { x: 0, y: 0 }; // New object on each call
  for (const point of points) {
    total.x += point.x;
    total.y += point.y;
  }
  return total;
}
```

#### ✅ More Ideal Example
```javascript
// Option 1: Reuse objects
function sumPointsInto(points, resultTarget) {
  resultTarget.x = 0;
  resultTarget.y = 0;
  for (const point of points) {
    resultTarget.x += point.x;
    resultTarget.y += point.y;
  }
}
const reusableSum = { x: 0, y: 0 };

// Option 2: Return primitives when possible
function getMagnitudeSquared(vector) {
  return vector.x * vector.x + vector.y * vector.y; // Returns number, no new object
}
```

### Manage object lifetimes effectively

**Why:** Short-lived objects are efficiently handled by Young Generation GC. Explicit dereferencing helps GC identify unreachable objects sooner.

#### ❌ Less Ideal Example
```javascript
let largeData = null;
function processData() {
  largeData = new Array(1000000).fill('some data');
  // ... use largeData ...
  // Forgetting to nullify largeData when done
}
```

#### ✅ More Ideal Example
```javascript
function processAndReleaseData() {
  let localLargeData = new Array(1000000).fill('some data');
  // ... use localLargeData ...
  console.log("Processing done, data length:", localLargeData.length);
  // localLargeData becomes eligible for GC when function exits
  
  // For longer-lived references:
  // this.largeDataInstance = null; // Explicit cleanup when done
}
```

### Be mindful of closures retaining large objects

**Why:** Closures retain references to parent scope variables. Long-lived closures can prevent garbage collection of large objects.

#### ❌ Less Ideal Example
```javascript
function attachDataProcessor(eventEmitter) {
  const largeResource = new Array(1000000).fill('expensive resource');
  const id = Math.random();

  eventEmitter.on('dataEvent', (data) => {
    // This closure captures `largeResource` and `id`
    console.log(`Processing data with resource ${id}:`, largeResource.length, data);
  });
  // largeResource stays in memory as long as listener exists
}
```

#### ✅ More Ideal Example
```javascript
function attachSelectiveDataProcessor(eventEmitter) {
  const largeResource = new Array(1000000).fill('expensive resource');
  const resourceLength = largeResource.length; // Capture only what's needed
  const id = Math.random();

  const listener = (data) => {
    // Closure only captures `resourceLength` and `id`
    console.log(`Processing data with resource ${id} (length ${resourceLength}):`, data);
  };
  
  eventEmitter.on('dataEvent', listener);

  // Provide cleanup mechanism
  return () => {
    eventEmitter.off('dataEvent', listener);
    console.log(`Listener for ${id} removed.`);
  };
}
```

### Case Study: Memory Leaks in Component Closures

In frameworks like React, if a component registers an event listener or exports a function to a global object (e.g., `window`), it creates a closure. If this closure captures a component-specific function like a state setter (`setState`), it creates a strong reference that can prevent the entire component, its props, state, and fiber node from being garbage collected, leading to significant memory leaks.

#### ❌ Problematic Example
```javascript
import React, { useState, useEffect } from 'react';

const LeakyComponent = () => {
  const [value, setValue] = useState(0);

  const handleResize = () => {
    // This function creates a closure that captures `setValue`.
    console.log('Resized, current value is:', value);
    // Because handleResize is attached to the global `window` object,
    // it holds a reference to `setValue`, which in turn keeps the
    // entire component's fiber alive even after it unmounts.
  };

  useEffect(() => {
    window.addEventListener('resize', handleResize);

    // No cleanup function is returned, so the listener is never removed.
  }, []); // The empty dependency array means this effect runs only once.

  return <div>Leaky Component: {value}</div>;
};
```

#### ✅ Solution
```javascript
import React, { useState, useEffect, useCallback } from 'react';

const FixedComponent = () => {
  const [value, setValue] = useState(0);

  // `useCallback` is used to memoize the function, but the key is the cleanup.
  const handleResize = useCallback(() => {
    // The logic remains the same, but its lifecycle is now managed.
    console.log('Resized, current value is:', value);
  }, [value]); // Dependency array ensures `handleResize` has the latest `value`.

  useEffect(() => {
    window.addEventListener('resize', handleResize);

    // The key to fixing the leak: return a cleanup function.
    // React will execute this when the component unmounts.
    return () => {
      window.removeEventListener('resize', handleResize);
      console.log('Resize listener removed. Component cleaned up.');
    };
  }, [handleResize]); // Effect re-runs if `handleResize` changes.

  return <div>Fixed Component: {value}</div>;
};
```

---

## Leveraging the JIT Compiler

V8's Just-In-Time compiler (TurboFan) optimizes frequently executed functions into efficient machine code.

### Write predictable, type-stable functions

**Why:** Functions called with consistent argument types (monomorphic) are easier to optimize than those with varying types (polymorphic/megamorphic).

#### ❌ Less Ideal Example
```javascript
function getValue(obj) {
  return obj.value; // 'value' could be number, string, boolean, etc.
}
getValue({ value: 10 });
getValue({ value: "hello" });
getValue({ value: true, otherProp: 1 });
```

#### ✅ More Ideal Example
```javascript
function getNumericValue(obj) {
  // Assumes obj.value is always a number
  return obj.value * 2;
}

function getStringRepresentation(obj) {
  // Assumes obj.representation is always a string
  return obj.representation.toUpperCase();
}

getNumericValue({ value: 10 });
getNumericValue({ value: 20 });
getStringRepresentation({ representation: "item" });
```

### Keep functions small and focused

**Why:** Smaller functions are more likely to be inlined by TurboFan, eliminating function call overhead and exposing more optimization opportunities.

#### ❌ Less Ideal Example
```javascript
function processUserData(user) {
  // Validation
  if (!user.name || user.name.length < 3) {
    console.error("Invalid name");
    return false;
  }
  if (!user.email || !user.email.includes('@')) {
    console.error("Invalid email");
    return false;
  }
  // Transformation
  const fullName = `${user.firstName} ${user.lastName}`;
  // Logging
  console.log(`Processing user: ${fullName}`);
  // Saving
  // db.save({ ...user, fullName });
  return true;
}
```

#### ✅ More Ideal Example
```javascript
function isValidName(name) {
  return name && name.length >= 3;
}

function isValidEmail(email) {
  return email && email.includes('@');
}

function getFullName(firstName, lastName) {
  return `${firstName} ${lastName}`;
}

function processUserDataOptimized(user) {
  if (!isValidName(user.name)) {
    console.error("Invalid name");
    return false;
  }
  if (!isValidEmail(user.email)) {
    console.error("Invalid email");
    return false;
  }
  
  const fullName = getFullName(user.firstName, user.lastName);
  console.log(`Processing user: ${fullName}`);
  // db.save({ ...user, fullName });
  return true;
}
```

### Avoid patterns that cause deoptimization

**Why:** Deoptimization occurs when V8's optimizing compiler discards optimized code due to broken assumptions, falling back to slower unoptimized code.

#### ❌ Less Ideal Example
```javascript
function sumArrayUnsafe(arr) {
  let sum = 0;
  for (let i = 0; i < arr.length; i++) {
    try { // try-catch inside hot loop can limit optimizations
      sum += arr[i].value;
    } catch (e) {
      sum += 0;
    }
  }
  return sum;
}
```

#### ✅ More Ideal Example
```javascript
function sumArraySafer(arr) {
  let sum = 0;
  for (let i = 0; i < arr.length; i++) {
    const element = arr[i];
    if (element && typeof element.value === 'number') {
      sum += element.value;
    }
    // Handle problematic elements with explicit checks
  }
  return sum;
}
```

---

## Asynchronous Operations

JavaScript's single-threaded event loop requires careful management of asynchronous operations.

### Avoid long-running synchronous operations

**Why:** Synchronous code blocks the event loop, preventing processing of user interactions, network responses, and timers.

#### ❌ Less Ideal Example
```javascript
function calculateComplexThingSync() {
  // Simulating a very long computation
  const end = Date.now() + 2000; // 2 seconds
  while (Date.now() < end) { /* busy wait */ }
  return 42;
}
// This would freeze the UI for 2 seconds
```

#### ✅ More Ideal Example
```javascript
// Option 1: Async with chunked work
async function calculateComplexThingAsync() {
  console.log("Calculation started...");
  await new Promise(resolve => setTimeout(resolve, 2000));
  console.log("Calculation finished.");
  return 42;
}

// Option 2: Web Worker for CPU-bound tasks
// main.js
const myWorker = new Worker('worker.js');
myWorker.onmessage = function(e) { 
  console.log('Result from worker:', e.data); 
}
myWorker.postMessage({ N: 1000000 });

// worker.js
self.onmessage = function(e) {
  let result = 0;
  for (let i = 0; i < e.data.N; i++) {
    result += Math.sqrt(i);
  }
  self.postMessage(result);
};
```

### Understand microtask vs. macrotask queue implications

**Why:** Promises schedule microtasks that are processed before the next macrotask. Long microtask chains can delay macrotasks, affecting responsiveness.

#### ❌ Less Ideal Example
```javascript
function recursivePromiseChain(count) {
  if (count <= 0) return Promise.resolve();
  return Promise.resolve().then(() => {
    console.log("Microtask:", count);
    return recursivePromiseChain(count - 1);
  });
}

setTimeout(() => console.log("Macrotask (setTimeout) executed"), 0);
recursivePromiseChain(10000); // Delays setTimeout significantly
```

#### ✅ More Ideal Example
```javascript
async function processBatchAsync(items) {
  for (let i = 0; i < items.length; i++) {
    await processItem(items[i]);

    // Periodically yield to allow other events to process
    if (i % 100 === 0 && i > 0) {
      console.log("Yielding to event loop...");
      await new Promise(resolve => setTimeout(resolve, 0));
    }
  }
}
```

---

### Overhead of Asynchronous

**Why:** Asynchronous operations introduce additional overhead, including context switching and event loop management.


## String and RegExp Optimizations

### Be mindful of string concatenation in loops

**Why:** While V8 optimizes simple concatenations well, many intermediate strings in tight loops can pressure the GC.

#### ❌ Less Ideal Example
```javascript
let resultString = "";
const iterations = 10000;
for (let i = 0; i < iterations; i++) {
  resultString += "Part " + i + "; "; // Creates many intermediate strings
}
```

#### ✅ More Ideal Example
```javascript
const parts = [];
const iterations = 10000;
for (let i = 0; i < iterations; i++) {
  parts.push("Part ", i, "; ");
}
const resultStringOptimized = parts.join("");
```

### Optimize complex regular expressions

**Why:** Poorly written regexes can cause catastrophic backtracking. Re-creating RegExp objects in hot loops is inefficient.

#### ❌ Less Ideal Example
```javascript
function extractValue(text) {
  // Re-creating RegExp object frequently
  const regex = new RegExp("value=(\\d+)");
  const match = text.match(regex);
  return match ? match[1] : null;
}
```

#### ✅ More Ideal Example
```javascript
const valueRegex = /value=(\d+)/; // Define once, outside hot function

function extractValueOptimized(.text) {
  const match = text.match(valueRegex);
  return match ? match[1] : null;
}
```

---

## General Best Practices

### Use built-in methods wisely

**Why:** Native JavaScript methods are implemented in C++ and highly optimized by V8. They're generally faster and safer than hand-rolled equivalents.

#### ❌ Less Ideal Example
```javascript
const numbers = [1, 2, 3, 4, 5];
const doubledNumbersManual = [];
for (let i = 0; i < numbers.length; i++) {
  if (numbers[i] > 2) {
     doubledNumbersManual.push(numbers[i] * 2);
  }
}
```

#### ✅ More Ideal Example
```javascript
const numbers = [1, 2, 3, 4, 5];
const doubledNumbersBuiltIn = numbers
  .filter(n => n > 2)
  .map(n => n * 2);
```

### Profile Your Code! (The Golden Rule)

**Why:** Performance optimization should be guided by data, not guesswork. Profiling identifies actual bottlenecks where optimization efforts will have the most impact.

#### Profiling Process:
1. **Identify** a performance concern
2. **Formulate** a hypothesis about the cause
3. **Use profiling tools:**
   - **Browsers:** Chrome DevTools (Performance tab, Memory tab)
   - **Node.js:** `node --prof` and `node --prof-process`, or `node --inspect`
4. **Analyze** results to find functions consuming the most CPU/memory
5. **Optimize** identified bottlenecks using relevant principles from this guide
6. **Re-profile** to confirm improvement
7. **Repeat** as necessary

#### Example Profiler Output:
```
- transformData: 75% CPU time
  - calculateSubValue: 40% (within transformData)
  - formatOutput: 30% (within transformData)
- renderUI: 15% CPU time
- other: 10% CPU time
```

Focus optimization efforts on `transformData` and its subfunctions for maximum impact.

---

## Summary

Performance optimization in V8 revolves around understanding how the engine works internally and writing code that aligns with its optimization strategies. The key principles are:

- **Predictability:** Consistent object shapes, types, and function signatures
- **Memory efficiency:** Minimize object churn and manage lifetimes
- **Event loop awareness:** Keep the main thread responsive
- **Data-driven optimization:** Always profile before optimizing

Remember: **Profile first, optimize second.** These principles provide a foundation, but real-world performance issues should always be identified through profiling and measurement.
