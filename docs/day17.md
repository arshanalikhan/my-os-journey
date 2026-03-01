# Day 17: Multitasking

Yesterday, the CPU was trapped in a single timeline
Today, it lives in parallel universes

this required building a task scheduler, giving each thread its own memory stack, and writing assembly to swap CPU registers on the fly

what’s happening in the image:
* MULTITASK command initializes the Task Control Blocks
* task A (green) prints and yields the CPU
* task B (red) prints and yields the CPU
* the scheduler switches the stack pointer and restores the next task’s register state
* two infinite loops running simultaneously on a single core without crashing.

allocate -> save state -> swap stack -> restore state -> success

 
