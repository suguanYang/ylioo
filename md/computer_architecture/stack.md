A stack is a continuous memory address used for _Control transfer_ and _Data transfer_

## Local Storage on the Stack
- There are not enough registers to hold all of the local data.
. 
- The address operator ‘&’ is applied to a local variable, and hence we must be
able to generate an address for it.
. 
- Some of the local variables are arrays or structures and hence must be accessed
by array or structure references. We will discuss this possibility when we
describe how arrays and structures are allocated.


## Declare a struct on the stack
```
typedef struct { 
  int field1;
  int field2;
} C;

void foo() { 
  C local; // simply declare it as a normal / non-pointer value
  local.field1 = 42;
}
```