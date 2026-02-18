# Day 10: Memory Management (The Heap)

Yesterday, every variable was static and fixed forever 
Today, the OS asks for more

this required building a placement allocator and writing my first kmalloc driver

## What’s happening in the image:
* heap initialized at a safe address
* kmalloc requests memory on the fly
* OS finds free RAM and returns a pointer
* data written to a dynamic location
* read back perfectly without crashing

Just request -> allocate -> write -> read -> success

![day10](https://github.com/user-attachments/assets/ad932ba0-1388-400e-95ae-09b6e310aa6b)
