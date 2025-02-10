---
title: "TypeScript Types Through Set Theory"
---

## The Object set

The object type is the infinite set of all possible object shapes;
an interface is the infinite set of all possible object shapes that have specific properties.
An interface is then a subset of the object set.
From the universe of all possible object shapes, those object shapes whose properties match the interface are assignable to it.
Since an interface describes the shape of an object, the more properties we add to the interface, the fewer object shapes will match, and so the smaller the set of possible values becomes.
Adding properties to an interface shrinks the set that it stands for, and vice versa.

## Interface union

the definition of union:
A = B ∪ C;
A = { for any x belongs to A, x also belongs to B or C or both}
so union make A much bigger than B or C.

When unionizing two interfaces, the output of the union need to match:

- one input type, or
- the other input type, or
- both.
  make the output interface broader
  example:

```
interface A {
  a: 1;
}

interface B {
  b: 1;
}
const x: A | B = { a: 1 }; // belongs to A
const y: A | B = { b: 1 }; // belongs to B
const z: A | B = { a: 1, b: 1 }; // or both
```

## Interface intersection

the definition of intersection:
A = B ∩ C;
A = { for any x belongs to A, x must belongs to B and C }
so intersection make A much smaller than B or C.

When intersecting two interfaces, the output of the intersection need to match:

- both

example:

```
interface A {
  a: 1;
}

interface B {
  b: 1;
}

const x: A & B = { a: 1 }; // fails
const y: A & B = { b: 1 }; // fails
const z: A & B = { a: 1, b: 1 }; // succeeds
```

## conditional types

when we pass a union type into a checked generic that conditional type resolution stops being straightforward and becomes open to interpretation.
When we pass a union to a generic in a conditional type,

-sdasdasdasd Check if each constituent of the union is a (proper) subset of the other type and resolve each type. Aggregate all resolved types in a union.
- Check if the union as a whole, meaning as a single set, is a (proper) subset of the other type and resolve the type.

The first interpretation is a distributive conditional type. Here, the check is distributed over each constituent of the union. This means that a question is asked of each union constituent, and a type is resolved based on the answer for each union constituent. This is TypeScript's default resolution strategy for a conditional type having a checked generic to which a union is passed.

```
// distributive conditional type
type ToArrayDist<T> = T extends unknown ? T[] : never;

// call to distributive conditonal type
type R = ToArrayDist<string | number>; // string[] | number[]
```

The second interpretation, operating on the union as a whole, is a non-distributive conditional type. Since distributivity is the default behavior, disabling distributivity requires wrapping each of the two types in the condition with square brackets([]). Non-distributivity is TypeScript's alternative resolution strategy for a conditional type having a checked generic to which a union is passed.

```
// non-distributive conditional type
type ToArrayNonDist<T> = [T] extends [unknown] ? T[] : never;

// call to non-distributive conditional type
type R = ToArrayNonDist<string | number>; // (string | number)[];
```

## the keyof union type

```
type n = keyof ({a: 1} | {b: 1}); // never
type ab = keyof {a: 1} & keyof {b: 1};

```

the union type of 2 type will produce 3 possible types, union type will only narrowed to specified type when it is later be used,
and the keyof opreate only return the accessible keys of a type, so n returns nerver since the operated type is not guaranteed
