Day 16: The Heap (Memory Recycling) 

Yesterday, memory was a one-way street where every allocation was a permanent leak.
Today, the OS recycles.

this required building a dynamic block allocator with hidden meta-headers to track free/used states.

What’s happening in the image:
* OS requests 100 bytes (malloc)
* Allocator hands over address 0x0001600C
* OS releases the pointer (free)
* OS requests 100 bytes again

Allocator searches the linked list, finds the newly freed block, and reuses 0x0001600C perfectly instead of taking new RAM

Just allocate -> free -> reallocate -> reuse -> success
