# Day 6 of building an OS from scratch (x86)

today was about abstraction and structure

## what i worked on:
* built a Port I/O driver (ports.c) to wrap low-level in and out assembly instructions, allowing the kernel (written in C) to safely communicate with hardware controllers.
*built a VGA screen driver (screen.c) to abstract direct video memory access and implement cursor positioning, text wrapping, and newline handling.
* wrote a Makefile to automate the build pipeline (GCC -> NASM -> LD -> CAT), reducing the entire boot process to a single command: make run.
* restructured the project by introducing a drivers/ directory to separate hardware logic from core kernel code.

the first screenshot is the output from make run (using QEMU’s -display curses mode)
the last two screenshots show a cursor blinking ( _ ) -- fully controlled by the kernel, not BIOS

<img width="2879" height="1798" alt="Screenshot 2026-02-07 173131" src="https://github.com/user-attachments/assets/aba5a740-b5ea-43af-bcd7-76d8590c2973" />
<img width="2879" height="1795" alt="Screenshot 2026-02-07 184950" src="https://github.com/user-attachments/assets/6cc4e4ab-ff7b-47c4-b9ba-d1a53b7cb739" />
<img width="2879" height="1799" alt="Screenshot 2026-02-07 184955" src="https://github.com/user-attachments/assets/be05cf66-bdb9-42d8-8961-a479d18da7a7" />
