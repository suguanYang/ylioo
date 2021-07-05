This is not a explaination of TC39 specs, just a javascript implementation perspective.

## Terms

### The Objects
An object is a data structure that contains data and methods, the `null` and `Primitive` are not object.

### The Constructors
The Constructors itself are callable objects, every constructors have a `constructor` method, it will be called when invoke `new constructor()`(the initializes). the constructor default `constructor` method points to itself. perform a `new` operator on constructor will create an object.

```javascript
function Klass() {
	this.name = 'a';
}

const a = new Klass();
a.constructor === Klass;
a.name === 'a';
```

### The Prototype
Every objects has a prototype, it can be found by `Object.getPrototypeOf`, the prototype is a constructor's `prototype` property.
the `constructor` method site on the `prototype` property. Every objects has a root prototype which is `Object.prototype`.

```javascript
function Klass() {
	this.name = 'a';
}
function klassConstructor() {
	this.name = 'b'
};
Klass.prototype.constructor = klassConstructor;

const a = new Klass();
a.constructor === klassConstructor;
a.name === 'b';
```
if a object's prototype is not an object, the new operator will set the `prototype` property of obj to the standard built-in Object prototype object.
```javascript
function Foo(){}
Foo.prototype = null;
Object.getPrototypeOf(new Foo()) === Object.prototype;
new Foo().constructor === Object;
```

### The prototype chain
Every objects have a `___proto__` property, any data or methods defined on `__proto__` can be shared fot that object. if object was inited by `new Constructor()` or `Object.create(Argument)`, it's `__proto__` property is an equivalent of it's constructor's prototype or Argument.
