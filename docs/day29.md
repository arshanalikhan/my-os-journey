# Day 29 of building my own Operating System from scratch: I finally have a True GUI Mouse Cursor! 🖱️🚀

Drawing a pixel on a screen is easy. Building a cursor that "floats" seamlessly over your UI without permanently erasing the pixels underneath it is a completely different beast.

## To make this work, I had to build a custom Compositing Engine in my VGA graphics driver. Dozens of times a second, the kernel has to:
1️. Save the background pixels currently under the mouse coordinates into a memory buffer
2️. Draw the custom 10x15 pixel Arrow Bitmap
3. Restore the saved background pixels when the mouse moves to "repair" the UI behind it

But the rendering logic was only half the battle. To get this running, I had to survive a gauntlet of low-level hardware debugging:

The Interrupt Storm: Debugging the 8259 PIC chips to ensure the PS/2 controller received the correct End of Interrupt (EOI) signals without locking up the CPU.

The LBA Disk Barrier: My kernel got so large that it exceeded legacy CHS sector limits. My Makefile started accidentally writing my userland apps directly on top of my kernel's interrupt handlers on the disk image! I had to rewrite my Assembly bootloader to use Modern LBA (Logical Block Addressing) via a Disk Address Packet (DAP) to expand my OS's hard drive capacity

Compiler vs. Hardware: Diagnosing a C compiler optimization bug where GCC cached my coordinate variables and ignored the live hardware RAM updates (fixed with the magic of the volatile keyword!)

Assembly Routing: Fixing macro bugs in my IDT (Interrupt Descriptor Table) that caused hardware IRQs to masquerade as software exceptions.

Seeing that arrow glide flawlessly over my custom typography and graphics without a single QEMU core dump made every crash worth it. Arshan OS officially has a Graphical User Interface!

