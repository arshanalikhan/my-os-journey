# Day 30 (Finally!): From a 16-bit "Hello World" to a 32-bit Graphical Window Manager 

I didn't build this in 30 consecutive days. Between studying and life, I've been chipping away at this project a few days a week over the last few months. No Linux kernel, no pre-built libraries—just raw C, Assembly, and bare-metal hardware

But after 30 dedicated coding sessions, I reached a massive milestone: I mapped out the entire architecture of my OS, and I successfully built a Draggable GUI Window Manager!

## here is a look under the hood at the actual directory tree I’ve built so far:

📂 myos/
├── Makefile (Compiles, links, and packs the 100-sector OS image) 
├── boot.asm (16-bit real mode bootloader using LBA/DAP)
├── kernel_entry.asm (The Assembly bridge to C)
│
├── 🧠 kernel/ (The OS Core)
│   ├── kernel.c (Main loop, Compositing Engine, Drag Logic) 
│   ├── mem.c (Dynamic memory allocator)
│   ├── syscall.c (Gateway for user apps)
│   └── task.c (Multitasking scheduler)
│
├── 🔌 drivers/ (Hardware Abstraction)
│   ├── mouse.c (PS/2 parser, tracks X/Y & left-clicks)
│   ├── keyboard.c (Scancode to ASCII translator)
│   ├── vga.c (Mode 13h pixel & rectangle plotting)
│   ├── gui_text.c (Custom 8x8 typography engine)
│   └── timer.c (PIT hardware clock)
│
├── ⚙️ cpu/ (x86 Architecture)
│   ├── isr.c / idt.c (Interrupt Service Routines & Tables)
│   ├── gdt.c (Global Descriptor Table / Security Rings)
│   └── paging.c (Virtual Memory mapping)
│
└── 🧑‍💻 userland/ (Application Layer)
└── app.c / libc.c (External apps & standard library clones)

To cap off Session 30, I upgraded the mouse driver to detect left-clicks, wrote bounding-box collision math, and programmed the OS to let me physically click and drag a GUI window across my custom graphical canvas without tearing the pixels beneath it

Building an OS teaches you that there is no "magic" inside a computer. Every single pixel, every hardware interrupt, and every byte of memory has to be explicitly managed. It has been the most frustrating and rewarding engineering challenge I've ever taken on



