# Day 7 of building an OS from scratch (x86) 

this one took 2 days->
 
after building the display driver on Day 6, I thought the next step would be straight forward, it wasn’t
 
for the last two days I’ve been working on giving the CPU “reflexes” that is implementing the Interrupt Descriptor Table (IDT)
   
I implemented the Interrupt Descriptor Table (IDT) so the processor knows where to jump when an event interrupts normal execution
   
## What I worked on: 
* defined the IDT gate structure (idt_gate_t) to strictly match the x86 hardware specification.
* wrote low-level Assembly ISR stubs (interrupt.asm) to save CPU state (push registers) before handing control to C.
* implemented the glue code (idt.c) to load the table into the CPU using the lidt instruction.
* built ISR handlers in C to verify control flow returns safely to the kernel.
* manually triggered a software interrupt (int $2) and confirmed the kernel caught it and resumed execution
 
the screenshot shows:  
installing ISRs -> interrupt triggered -> INTERRUPT RECEIVED -> back in kernel
  
I didn’t post this immediately after day 6 because this part required debugging macro redefinitions, linker quirks, and assembly label conflicts

<img width="2878" height="1798" alt="Screenshot 2026-02-14 110117" src="https://github.com/user-attachments/assets/184da59b-5794-4bf1-a651-9e40217558b3" /> 
 
