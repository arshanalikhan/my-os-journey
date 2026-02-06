Day 5 of building an OS from scratch (x86)

until this day i was writing in human readable machine code but to be fast enough C is introduced to this environment

what i worked on:

* used the freestanding c concept to write into kernel
* used linker (ld) to merge bootloader and kernel
* mapped the memory at specific address(0x1000) 
* also checked the error handling by entering more number of sectors than actually required (9<15)

"Xuccessfully" landed in 32-bit Protected Mode - yes that x is intentional as it was overwritten from the c kernel

