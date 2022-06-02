This is not an explanation of TC39 specs, just a javascript implementation perspective.

## Terms

### The Objects
An object is a data structure that contains data and methods, the `null` and `Primitive` are not object.

### The Constructors
The Constructors itself are callable objects, every constructors have a `constructor` method site on the *prototype* properties, it will be called when initializes object. the constructor default `constructor` method points to itself. 

```javascript
function Klass() {
	this.name = 'a';
}

const a = new Klass();
a.constructor === Klass;
a.name === 'a';
```

### The Prototype
Every objects has a prototype, it can be found by `Object.getPrototypeOf`, Every objects has a root prototype which is `Object.prototype`.

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
if a object's `prototype` is not an object, the new operator will set the `prototype` property of obj to the standard built-in Object prototype object.
```javascript
function Foo(){}
Foo.prototype = null;
Object.getPrototypeOf(new Foo()) === Object.prototype;
new Foo().constructor === Object;
```

### The prototype property
The `prototype` property is used to initializes the `__proto__` property of it's instance.(prototype pattern)

### The prototype chain
Every objects have a `___proto__` property, any data or methods defined on `__proto__` can be shared for that object. if object was initialized by `new Constructor()` or `Object.create(Argument)`, it's `__proto__` property is an equivalent of it's constructor's `prototype` property or Argument.
