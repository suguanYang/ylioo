---
title: "Memory Paging and Page Table Implementation"
---

The physical memory size unit is awalys Byte, consider the physical memory as a large array, the size of the array is the physical memory size, and the element of the array is the page frame, and the index of the array is the page frame number, so the page frame number is also a kind of address.

Paging per process can used lots of memory, the inverted page table is a good way to save memory, but it increase the time complexity of the page table lookup since it was sorted by physical address, a virtual address lookup awlays need to traverse the whole page table, in contrast, the page table is sorted by virtual address in the normal page table which is sorted by virtual address, we can caculate the frame number.