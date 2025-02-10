---
title: "Store Buffer and Memory Performance"
---

The store unit includes a store buffer
containing the addresses and data of the store operations that have been issued
to the store unit, but have not yet been completed, where completion involves
updating the data cache. This buffer is provided so that a series of store operations
can be executed without having to wait for each one to update the cache. When
a load operation occurs, it must check the entries in the store buffer for matching
addresses. If it finds a match (meaning that any of the bytes being written have the
same address as any of the bytes being read), it retrieves the corresponding data
entry as the result of the load operation.