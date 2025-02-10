---
title: "Hash Table Implementation and Methods"
---

CHAINED-HASH-INSERT(T, x)
    LIST-PREPEND(T[h(x.key)], x)
CHAINED-HASH-SEARCH(T, k)
    return LIST-SEARCH(T[h(k)], k)
CHAINED-HASH-DELETE(T, x)
    LIST-DELETE(T[h(x.key)], x)
```

The division method
```
h(k) = k mod m
```
The multiplication method
```
h(k) = ⌊m (kA mod 1)⌋ // "kA mod 1" means the fractional part of kA
```

## Open addressing
```
HASH-INSERT(T, k)
    i = 0
    repeat
        q = h(k, i)
        if T[q] == NIL
            T[q] = k
            return q
        else i = i + 1
    until i == m
    error "hash table overflow"

HASH-SEARCH(T, k)
	i = 0
    repeat
        q = h(k, i)
        if T[q] == k
            return q
        i = i + 1
    until T[q] == NIL or i == m
    return NIL
```
