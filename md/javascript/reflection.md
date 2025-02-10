---
title: "JavaScript Reflection and Proxy API"
---

Javascript has built-in support for introspection and self-modification. These features
are provided as part of the language, rather than througt a dusticnt metaobject protocol.
This is largely because Javascript objects are represented as flexible records mapping key
to value. Property names can be computed at runtime and their value can retrived using arring
index notation.

## Proxy
The behavior of a proxy object is controlled by a separate handler object. The methods of the
handler object are traps that are called whenever a corresponding operation is applied to
the proxy object. Handlers are effectively "meta-objects" and their interface effectively
defines a "metaobject protocol".
The distinction between a proxy and its handler object enforces stratification(separation) of
the traps. Traps are not defined as part of the (application-level) interface of the
proxy object, but as part of the interface of the handler. For instance, the property
access proxy.has will not trigger the proxy's corresponding has trap. Instead, it
will correctly trigger handler.get(target,"has",proxy). Likewise, proxy.get triggers
handler.get(target,"get",proxy). Traps can only be invoked as methods on a proxy's
handler, not on the proxy itself. This enforces stratification (the meta-level traps should
not interfere with base-level method names). Thus, proxies continue to work correctly
if an application (by accident or by design) uses the names get, set, has, etc.
Separating handler and proxy into separate objects has other benefits. The handler
has its own prototype chain which is completely independent from that of its proxy. A
single handler may also handle multiple proxies. Indeed, all handler traps are parameterized
with the target to operate on, so that a shared handler can distinguish the different targets
of its proxies. The handler can even be a proxy itself.

**Stratification**: by defining a proxy's traps on a separate handler object, the proxy's
application-level interface remains cleanly separated from its meta-level interface.

## Functions
In Javascript, functions are objects. However, they differ from non-function objects in
a number of ways. In particular, functions support two operations not applicable to
objects: function application and object construction. Construction is performed using
the new operator: if F is a function, new F() creates a new object o whose prototype is
F.prototype. F is the applied, with its this-pseudovariable bound to o, so that it can
initialize the new object. Think of the new operator as a way of invoking a constructor
in class-based languages.

The apply and construct traps are only enabled when the wrapped target is itself a
function. If this is not the case, calling proxy(...args) or new proxy(...args) results
in an error, just like when trying to apply or construct a non-function value3
. The
following code snippet illustrates the interaction between functions and proxies. It
defines a proxy p that wraps a function f and acts as a simple contract, enforcing that
a) the function is only called with numbers and b) it is never used as a constructor.

```
var f = function ( a , b ) { return a+b ; };
var h = {
    apply: function ( target , receiver , args ) {
        args.forEach(function ( arg ) { assert ( Number ( arg ) === arg ) ; } ) ;
        return Reflect.apply ( target , receiver , args ) ;
    } ,
    construct: function ( target , args ) {
        throw new Error ( " not a constructor " ) ;
    }
};

var p = Proxy(f, h) ;
f(1, 2); // returns3
p(1, 2); // callsh.apply(f, undefined, [ 1 , 2 ] ) , returns 3
p('a', 'b') ; // throws exception
new p(1, 2) ; // throws exception
p.x / / get trap missing, defaults to f.x, returns undefined
var o = { m : p };
o.m(1, 2) ; // calls h.apply(f, o , [1, 2]) , returns 3
```
The apply trap receives as its second argument the value to use for the this
pseudovariable. When a function is applied without a receiver, as in the expression
p(1,2), this parameter is set to undefined. When a function is stored as a property
of an object and invoked as a method, as in the expression o.m(1,2), this parameter
is set to the receiver object o.

## Reflection
reflective programming or reflection is the ability of a process to examine, introspect,
and modify its own structure and behavior, it also a key strategy for metaprogramming.
In javscript, Reflection is provided by the Reflect object. it is a built-in object that provides
methods for interceptable JavaScript operations. The methods are the same as  proxy handlers.

### Reflect: the dual of the Proxy API
When writing a Proxy handler, one is often interested in augmenting the default behavior of
the target object in response to an intercepted operation. As such, a generic mechanism is
needed by which the implementor of a handler trap can "forward" the intercepted operation to
its target. 

The Proxy API provides a distinct Reflect object5 which defines, for each trap in the
Proxy API, a method with the same name and arguments. When invoked, the method
applies the intercepted operation to its first parameter. The Reflect object is the dual 
of a Proxy handler object: a proxy handler can uniformly intercept operations on an object, 
while the Reflect object can uniformly perform these operations on an object. 

## References

On the design of the ECMAScript Reflection API
MDN web docs: Reflect