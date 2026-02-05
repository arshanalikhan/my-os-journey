Day 3 of building an OS from scratch (x86)

yesterday kernel code was already executing, but today the threshold of 512 bytes is crossed intentionally and correctly


what i worked on:

* loading the kernel from disk using BIOS INT 0x13

* controlling where the kernel is placed in memory and how execution is transferred

* learning different string methods in both bootloader(BIOS) and kernel(VGA)

* experimented with different QEMU display modes(-display curses) to get full screen output

today wasn't about learning new concepts rather learning new methods of already known parameters
<img width="2879" height="1799" alt="Screenshot 2026-02-03 002004" src="https://github.com/user-attachments/assets/12252518-14b6-4e1f-afed-e34147007c64" />
