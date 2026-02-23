Day 14: The Invisible Shield (Virtual Memory & Paging) 

Up until today, my OS has been living dangerously. It used direct Physical Memory. If a program accidentally wrote to address 0x0, it would overwrite the BIOS and instantly crash the entire computer

today, I implemented Paging

Paging introduces a layer of deception called Virtual Memory. Now, when a program asks for memory, the CPU checks my OS's "Page Directory" and "Page Tables" to secretly map that virtual address to a safe physical RAM frame (in 4KB chunks)

the test (and the "Success" Crash):
to prove my Invisible Shield was working, I wrote a CRASH command in my shell that intentionally tried to read an unmapped, illegal memory address (0xA0000000).

if Paging was off, the OS would have blindly read the garbage and kept going. Instead? the CPU's Memory Management Unit instantly blocked the read, threw a Page Fault, and triggered a hard reboot of the emulator

Never been this happy when the system crashes :)
