opaque types are those which allow you to hold a handle (i.e., a pointer) to an structure, but not modify or view its contents directly (if you are allowed to at all, you do so through helper functions which understand the internal structure).

Opaque types are, in part, a way to make C more object-oriented. They allow encapsulation, so that the internal details of a type can change--or be implemented differently in different platforms/situations--without the code that uses it having to change.


## ABI
It is the most generally used for library purpose. The main principe behind Opaque type in c is to use data though its pointer in order to hide data handling implementation. Since the implementation is hidden, you can modify the library without recompiling any program which depend on it