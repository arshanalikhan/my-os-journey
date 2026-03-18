#include "idt.h"
#include "../drivers/screen.h"

// Define the IDT and the Pointer
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    // 0x8E = 1 (Present) | 00 (Ring 0) | 01110 (32-bit Interrupt Gate)
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}

void set_idt() {
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    
    // Debug print
    kprint("Loading IDT...\n");
    
    // Load the IDT pointer
    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
    
    kprint("IDT Loaded.\n");
}
