## Replacement Selection
Replacement selection works as follows. Assume that the main processing is done in an array of size M records.

1. Fill the array from disk. Set LAST = M-1.
2. Build a min-heap. (Recall that a min-heap is defined such that the record at each node has a key value less than the key values of its children.)
3. Repeat until the array is empty:
4. Send the record with the minimum key value (the root) to the output buffer.
5. Let R be the next record in the input buffer. If R‘s key value is greater than the key value just output …
6. Then place R at the root.
7. Else replace the root with the record in array position LAST, and place R at position LAST. Set LAST = LAST - 1.
8. Sift down the root to reorder the heap.
