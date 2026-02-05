Day 2 of Building an OS from scratch (x86) 

what i worked on:
* learned control flow at machine level (jmp$ , jmp 0x7c00) 
* handed control from bootloader to kernel 
* wrote a minimal kernel that directly writes to VGA memory (0xB8000) 
* understood why kernels must never end 
* learned why an infinite loop in a kernel is intentional and not a “freeze” 
* learned where BIOS stops helping and why real OS kernels avoid BIOS services 
* successfully displayed kernel output (KERNEL) after boot 


Today was full of set backs, repeated attempts, multiple problems and a long 5 hour session of trial and error but in the end learning is 
once the kernel starts, you own the hardware... just raw CPU+memory #OperatingSystems 

 
