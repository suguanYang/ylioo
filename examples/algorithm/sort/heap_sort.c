// /*
// * the max-heapify assume the <bold>sub-tree LEFT(i) and RIGHT(i) are max-heaps<bold>, but A[i]
// * may be smaller than its children, thus its violating the property, max-heapify then
// * float down A[i] to make subtree rooted at A[i] follow the max-heap property
// */
// MAX-HEAPIFY(A, i)
//   l = LEFT(i)
//   r = RIGHT(i)
//   largest = i
//   if l > A.size
//     return
//   if A[l] > A[largest]
//     largest = l
//   if A[r] > A[largest]
//     largest = r
//   if lagest != i
//     swap(A, i, largest)
//     MAX-HEAPIFY(A, largest)

// # the Leave nodes index will start from n/2
// Proof: the last index of node is n, its parent PARENT(n) will be the latest parent that have children
//        thus the index of leave will start from PARENT(n), which is n/2

// BUILD-MAX-HEAP(A, n)
//   A.heap_size = n
//   for i = n/2, i >= 0 i++ # we only need HEAPIFY non-leave nodes, starts from the parent of leave nodes which follow the
//     MAX-HEAPIFY(A, i)     # max-heap property of its LEFT and RIGHT

// HEAP-SORT(A, n)
//   BUILD-MAX-HEAP(A, n)
//   for i = 0, i < n, i++
//     SWAP(A, 0, A.heap_size - 1)
//     A.heap_size--
//     MAX-HEAPIFY(A, 0)

// PRIORITY-QUEUE-DEQUEUE(A)
//   max = A[0]
//   A[0] = A[A.heap_size - 1]
//   A.heap_size--
//   MAX-HEAPIFY(A, 0)
//   return max

// PRIORITY-QUEUE-INCREASE-KEY(A, i, k)
//   if A[i].key > k
//     Err
//   A[i].key = k
//   while i > 0 && A[i].key > A[PARENT(i)] # This differ from `float down` process in the max-heapify proceduer
//     SWAP(A, i, PARENT(i))                # which float the A[i] to the root
//     i = PARENT(i)

// PRIORITY-QUEUE-ENQUEUE(A, node, n)
//   if A.heap_size == n
//     Err
//   A.heap_size += 1
//   key = node.key
//   node.key = -Infinity
//   A[heap_size - 1] = node
//   PRIORITY-QUEUE-INCREASE-KEY(A, heap_size - 1, k)

// BUILD-MAX-HEAP(A, n)
//   A.heap_size = 1
//   for i = 1 to n
//     PRIORITY-QUEUE-ENQUEUE(A, A[i], n)