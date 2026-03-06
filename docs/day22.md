# Day 22: Userland! Loading Real Executables 

My Operating System is officially no longer just a Kernel, it now has a functional Userland!

Until today, all commands were hardcoded into the Kernel itself. Today, I wrote a completely separate, standalone C application (app.c), compiled it into a real .elf file, and built an ELF Loader to dynamically map it into physical memory

## To get here, I had to:
* upgrade my 16-bit bootloader to use LBA (Logical Block Addressing) so it could load a massive Kernel + Virtual Disk payload without crashing into cylinder/head boundaries
* shift my Kernel's memory map to 0x8000 to prevent the OS from overwriting its own bootloader.
* build a Program Header parser to read the ELF "cargo manifest" and map the .text and .rodata segments into their exact requested physical RAM addresses

## what’s happening in the image:
the OS reads the .elf binary, dynamically maps three memory segments, jumps the CPU to the entry point, executes the standalone C program (which prints via my custom Syscalls), and safely resumes Kernel control when the app finishes!
![day22](https://github.com/user-attachments/assets/af9e478e-44e4-424c-89f9-06e363905171)
