First step into Operating System development 

Today I successfully wrote and booted my own x86 bootloader using NASM and QEMU 
The bootloader runs in 16-bit real mode and is loaded by the BIOS at 0x7C00 . This prints output directly using BIOS interrupts - no windows, no Linux, no libraries

This marks my first step towards building my own custom operating system from scratch. 
learned a lot about:
* how PCs actually boot
*memory layout at startup
*bare-metal programming 
