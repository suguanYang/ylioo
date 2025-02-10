---
title: "Structure Return Patterns in C"
---

void make_something(something_t *object) 
is the most common way to use structures in C. You leave the allocation to the caller. It is efficient but not pretty. and it also helpful when the function
need to return a code to the caller.


something_t make_something(void);
When something_t is small (read: copying it is about as cheap as copying a pointer) and you want it to be stack-allocated by default


When something_t is large or you want it to be heap-allocated, and also its ABI stable
something_t *make_something(void);
