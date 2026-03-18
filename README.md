# Arshan OS 🚀 

**A 32-bit Graphical Operating System built entirely from scratch in C and x86 Assembly.**

![C](https://img.shields.io/badge/Language-C-blue.svg) ![Assembly](https://img.shields.io/badge/Language-x86_Assembly-red.svg) ![Tools](https://img.shields.io/badge/Tools-GCC_%7C_NASM_%7C_QEMU-orange.svg)

I didn't build this in 30 consecutive days. Between studying and life, I've been chipping away at this project a few days a week. No Linux kernel, no pre-built libraries (`<stdio.h>`, `<stdlib.h>`), and no third-party bootloaders like GRUB. 

But after 30 dedicated coding sessions, I reached a massive milestone: building a fully functional operating system from absolute bare metal, where every pixel, interrupt, and memory allocation is explicitly managed by custom code.

<p align="center">
  <img src="[Insert Screenshot link here]" alt="Arshan OS GUI Window Manager" width="700">
</p>

## ✨ Key Features Built

What started as a 16-bit "Hello World" bootloader evolved into a complex 32-bit system featuring:

* **Custom Bootloader:** 16-bit to 32-bit Protected Mode transition, utilizing Modern LBA (Logical Block Addressing) to load a massive kernel via a Disk Address Packet (DAP).
* **Virtual Memory (Paging):** Protected kernel memory mapping and CPU privilege rings.
* **Dynamic Memory Manager:** A custom `malloc()` and `free()` heap allocator using hidden block metadata to recycle RAM.
* **Preemptive Multitasking:** Hardware-driven CPU time-slicing using the Programmable Interval Timer (PIT).
* **Ring 3 Security & Syscalls:** User Mode sandboxing that isolates third-party apps, utilizing `int 0x80` system calls to communicate safely with the Kernel.
* **Executable Loader:** A custom ELF (Executable and Linkable Format) parser that dynamically maps and executes `.elf` binaries from a Virtual Disk.
* **RamFS (File System):** Basic read/write file system for storing text files in memory.
* **Graphical User Interface:**
  * VGA Mode 13h (320x200, 256 colors) pixel engine.
  * Custom 8x8 bitmap typography.
  * Stateful PS/2 Mouse & Keyboard drivers.
  * Real-time Compositing Engine powering a **Draggable Window Manager**.

## 📂 Architecture

```text
my-os-journey/
├── Makefile              # Compiles C/ASM, links, and packs the 100-sector OS image
├── boot.asm              # 16-bit LBA Bootloader
├── kernel_entry.asm      # Assembly bridge to C
│
├── kernel/               # 🧠 The OS Core
│   ├── kernel.c          # Main loop, Compositing Engine, Drag Logic
│   ├── mem.c             # Dynamic memory allocator (Heap)
│   ├── syscall.c         # int 0x80 Gateway for user apps
│   ├── task.c            # Multitasking scheduler
│   └── string.c          # Custom string library clones
│
├── drivers/              # 🔌 Hardware Abstraction Layer
│   ├── mouse.c           # PS/2 parser, tracks X/Y & left-clicks
│   ├── keyboard.c        # Scancode to ASCII translator
│   ├── vga.c             # Mode 13h pixel & primitive drawing
│   ├── gui_text.c        # Custom 8x8 typography engine
│   ├── timer.c           # PIT hardware clock (Uptime & Sleep)
│   └── fs.c              # RAM File System
│
├── cpu/                  # ⚙️ x86 Architecture
│   ├── isr.c / idt.c     # Interrupt Service Routines & Tables
│   ├── gdt.c             # Global Descriptor Table (Security Rings)
│   └── paging.c          # Virtual Memory mapping
│
├── userland/             # 🧑‍💻 The Application Layer
│   └── app.c / libc.c    # External ELF apps & standard library wrappers
│
└── docs/                 # 📓 Daily journey documentation
```

## 🛠️ How to Build and Run

To compile and emulate this OS on your own machine, you will need a Linux environment (or WSL) with `gcc`, `nasm`, and `qemu` installed.

```bash
# 1. Install Dependencies (Ubuntu/Debian)
sudo apt install build-essential nasm qemu-system-x86

# 2. Compile and Launch the OS
make clean
make run
```

## 🛡️ Lessons Learned

Building an OS strips away all modern programming conveniences. This project involved grueling low-level debugging, including:
* Surviving **Triple Faults** and QEMU core dumps.
* Silencing **Interrupt Storms** caused by PS/2 buffer desyncs and IDE controllers.
* Bypassing compiler caching bugs by understanding memory-mapped I/O and `volatile` hardware variables.
* Solving compiler sign-extension traps (`push byte` vs `push dword`) in assembly macros.
