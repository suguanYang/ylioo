---
title: Performance
---

- Eliminating unneeded memory references
Holding the accumulated value in local variable acc (short for “accumulator”) eliminates the need to retrieve
it from memory and write back the updated value on every loop iteration.
```c
/* Accumulate result in local variable */
void combine4(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;
    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}
```