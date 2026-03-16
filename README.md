# OS Development Journey 
 


This repository documents my daily progress while learning

low-level systems programming and operating system development

from scratch. 
  
  
    
## Structure 

- docs        → Daily learning logs

- bootloader → Bootloader-related work

- kernel     → Kernel-related work

- images     → Screenshots and diagrams

 

### Current Status 
day 30
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




## Goal

To build a custom operating system (integrating my both engineering branches; CE & CSE ) step by step while

documenting everything I learn publicly.



