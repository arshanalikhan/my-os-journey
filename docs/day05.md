# Day 5 of building an OS from scratch (x86)

until this day i was writing in human readable machine code but to be fast enough C is introduced to this environment

## what i worked on:

* used the freestanding c concept to write into kernel
* used linker (ld) to merge bootloader and kernel
* mapped the memory at specific address(0x1000) 
* also checked the error handling by entering more number of sectors than actually required (9<15)

"Xuccessfully" landed in 32-bit Protected Mode - yes that x is intentional as it was overwritten from the c kernel

<img width="2880" height="1800" alt="Screenshot 2026-02-05 144714" src="https://github.com/user-attachments/assets/dd69d89b-9ab3-47e2-b4a1-d66e4c739c4c" />
<img width="1834" height="996" alt="Screenshot 2026-02-05 144453" src="https://github.com/user-attachments/assets/ed03c285-8ee7-4754-bf44-b5bb53a2b5de" />
