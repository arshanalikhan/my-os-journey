#include "syscall.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h" // We need access to get_app_input!

extern void isr128();

void syscall_handler(registers_t *regs) {
    if (regs->eax == 1) {
        // Syscall 1: Print String
        kprint_color((char *)regs->ebx, 0x0E); // Yellow text for apps
    }
    else if (regs->eax == 2) {
        // Syscall 2: Ping Test
        kprint_color("Kernel: Syscall 2 triggered!\n", 0x0A);
    }
    else if (regs->eax == 3) {
        // --- NEW: Syscall 3: Read String ---
        // EBX holds the memory address of the string buffer inside the App!
        get_app_input((char *)regs->ebx);
    }
}

void init_syscalls() {
    set_idt_gate(128, (u32)isr128);
    register_interrupt_handler(128, syscall_handler);
}

void syscall_print(char *message) {
    __asm__ __volatile__("int $0x80" : : "a"(1), "b"(message));
}
