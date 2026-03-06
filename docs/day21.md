# Day 21: The ELF Executable Loader (Reading Raw Binary)

Up until today, every command my Operating System could run was hardcoded directly inside the Kernel. But real computers don't work like that, they load and execute external third-party applications

today, I taught my OS how to read "foreign" machine code by building an ELF (Executable and Linkable Format) Parser!

to test the engine without relying on the file system just yet, I fed the Kernel a raw array of hex numbers representing a fully compiled, minimal 32-bit application

## what’s happening in the image:
* the Kernel scans the raw data and successfully verifies the 4-byte Magic Number (0x7F 'E' 'L' 'F') to confirm it's a valid application
* it parses the 52-byte header to dynamically locate the exact memory offset where the executable machine code begins
* the OS takes a leap of faith, jumping the CPU into that raw memory address
* the "alien" application wakes up, successfully triggers int 0x80 (Syscall 2) to communicate with the Kernel, and gracefully returns control without crashing the system!

Just parse header -> verify magic number -> find entry point -> execute -> success
![day21](https://github.com/user-attachments/assets/cb6a3d81-79c1-4c14-95f8-078bf4c1b1de)
