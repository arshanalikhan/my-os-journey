# Day 8: The Keyboard Driver (x86)

Yesterday, the OS was a silent movie
Today, it listens

this took debugging triple faults, a silent PIC, and a stack corruption bug

## What’s happening in the video:
* PIC remapped (IRQs 32–47)
* Keyboard interrupt enabled
* Raw scancodes read from port 0x60
* Converted into ASCII
* Printed by my kernel

Just hardware -> IDT -> ISR -> C handler -> screen
And it finally works
