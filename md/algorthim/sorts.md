---
title: "Sorting Algorithms: Merge Sort, Quick Sort and Heap Sort"
---

### Merge Sort
the merge sort algorithm has a total cost of BigTheta(nlgn),
the MERGE process requires extra memory linear to number of 
elements to be sorted 
```
MERGE(A, p, q, r):
    L_LEN = q - p + 1
    L = [1...L_LEN]
    R_LEN = r - q
    R = [1...R_LEN]

    for i = 1 to L_LEN
        L[i] = A[p + i - 1]

    for j = 1 to R_LEN
        R[j] = A[p + j]
    
    L[L_LEN + 1] = +Infinity
    R[R_LEN + 1] = +Infinity

    l, r = 1
    
    for k = p to r
        if L[l] <= R[r]:
            A[k] = L[l]
            l += 1
        else
            A[k] = R[r]
            r += 1

MERGE_SORT(A, p, r):
    if p < r
        q = floor((r + p) / 2)
        MERGE_SORT(A, p, r)
        MERGE_SORT(A, r + 1, q)
        MERGE(A, p, q, r)

```

### Quick Sort
The quicksort algorithm has a worst-case running time of BigTheta(n^2) on an input array
of n numbers. Despite this slow worst-case running time, quicksort is often the best
practical choice for sorting because it is remarkably efficient on the average: its
expected running time is BigTheta(nlgn), and the constant factors are quite small. 
It also has the advantage of sorting in place,
and it works well even in virtual-memory environments.
```
PARTITION(A, p, r):
    pivot = A[r]

    lower_idx = p - 1
    for i = p to r - 1
        if A[i] <= pivot:
            lower_idx += 1
            swap(A, i, lower_idx)
    
    swap(A, lower_idx + 1, r)
    return lower_idx + 1

QUICK_SORT(A, p, r):
    if p < r
        q = PARTITION(A, p, r)
        QUICK_SORT(A, p, q)
        QUICK_SORT(A, q + 1, r)

```

### Heap Sort
Like merge sort, but unlike insertion sort, 
heapsort's running time is O.n lg n/. Like 
insertion sort, but unlike merge sort, heapsort 
sorts in place: only a constant number of array
elements are stored outside the input array at any time.

```
MAX-HEAPIFY(A, i):
    heap_size = A.size
    largest = i
    if A[LEFT(i)] > A[largest] and LEFT(i) <= heap_size
        largest = LEFT(i)
    if A[RIGHT(i)] > A[largest] and RIGHT(i) <= heap_size
        largest = RIGTH(i)

    if i != largest
        swap(A, i, largest)
        MAX-HEAPIFY(A, largest)

BUILD-HEAP(A):
    A.size = length(A)
    for i = floor(length(A) / 2) to 1   // At the start of each iteration of the for loop i is the root of a max-heap.
        MAX-HEAPIFY(A, i)

HEAP-SORT(A):
    A = BUILD-HEAP(A)
    for i = length(A) to 1
        swap(A, 1, i)
        A.size -= 1
        MAX-HEAPIFY(A, 1)
```