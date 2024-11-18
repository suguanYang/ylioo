
The physical memory size unit is awalys Byte, consider the physical memory as a large array, the size of the array is the physical memory size, and the element of the array is the page frame, and the index of the array is the page frame number, so the page frame number is also a kind of address.

Frequently, on a 32-bit CPU, each page-table entry is 4 bytes long, but that
size can vary as well. A 32-bit entry can point to one of 232 physical page
frames. If the frame size is 4 KB (212), then a system with 4-byte entries can
address 244 bytes (or 16 TB) of physical memory. We should note here that the
size of physical memory in a paged memory system is typically different from
the maximum logical size of a process