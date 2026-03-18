#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *r) {
    if (r->int_no >= 40) port_byte_out(0xA0, 0x20); 
    port_byte_out(0x20, 0x20); 
    
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
}

extern void isr32(); extern void isr33(); extern void isr34(); extern void isr35();
extern void isr36(); extern void isr37(); extern void isr38(); extern void isr39();
extern void isr40(); extern void isr41(); extern void isr42(); extern void isr43();
extern void isr44(); extern void isr45(); extern void isr46(); extern void isr47();

void irq_install() {
    port_byte_out(0x20, 0x11); port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20); port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04); port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01); port_byte_out(0xA1, 0x01);
    
    // --- THE UNMUTE FIX ---
    // 0xF8: Unmask Timer(0), Keyboard(1), Cascade(2)
    port_byte_out(0x21, 0xF8); 
    // 0xEF: Unmask Mouse(12) on the Slave PIC!
    port_byte_out(0xA1, 0xEF); 

    set_idt_gate(32, (u32)isr32); set_idt_gate(33, (u32)isr33); 
    set_idt_gate(34, (u32)isr34); set_idt_gate(35, (u32)isr35);
    set_idt_gate(36, (u32)isr36); set_idt_gate(37, (u32)isr37);
    set_idt_gate(38, (u32)isr38); set_idt_gate(39, (u32)isr39);
    set_idt_gate(40, (u32)isr40); set_idt_gate(41, (u32)isr41);
    set_idt_gate(42, (u32)isr42); set_idt_gate(43, (u32)isr43);
    set_idt_gate(44, (u32)isr44); // Mouse is active again!
    set_idt_gate(45, (u32)isr45); set_idt_gate(46, (u32)isr46);
    set_idt_gate(47, (u32)isr47);

    set_idt(); 
}

void isr_handler(registers_t *r) {
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r); 
        return;     
    }
}

extern void isr13();
extern void isr14();
extern void isr128();

void isr_install() {
    set_idt_gate(13, (u32)isr13); 
    set_idt_gate(14, (u32)isr14); 
    set_idt_gate(128, (u32)isr128); 
}
