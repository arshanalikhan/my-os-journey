# Day 24: Building the C Standard Library (libc)

Yesterday, my OS loaded an external app, but its text strings were completely invisible because the compiler scattered them across unmapped memory segments.
Today, the apps have a voice.

this required building a custom libc to wrap complex assembly syscalls into clean C functions and mastering GCC linker flags.

## what’s happening in the image:
* a standalone C application is compiled using my custom libc.h.
* the Linker's -N (OMAGIC) flag forces the .rodata (strings) and .text (code) into the exact same memory block.
* the OS dynamically loads APP.ELF from the virtual hard drive.
* the app successfully uses the print() wrapper to trigger int 0x80 and pass its strings safely to the Ring 0 Kernel.
* the Userland app successfully prints formatted text to the screen!

Just compile -> link data & code -> trap to kernel -> print -> success

#OperatingSystems #OSDev #x86 #KernelDevelopment #SystemsProgramming #CProgramming #CompilerDesign #Linker #GCC #QEMU

<img width="1544" height="1030" alt="Screenshot 2026-03-06 144343" src="https://github.com/user-attachments/assets/154c60f7-204c-4b5f-bdc6-c0c7f2805e4a" />
