#include "timer.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "../kernel/task.h" // We need access to the scheduler!

volatile unsigned int tick = 0; 
extern int scheduler_running;   // Grab the flag from kernel.c

static void timer_callback(registers_t *regs) {
    tick++; 
    
    // --- PREEMPTIVE SCHEDULING LOGIC ---
    // If the scheduler is active, force a task swap every 5 ticks!
    if (scheduler_running == 1 && (tick % 5 == 0)) {
        thread_yield(); 
    }
    // -----------------------------------
}

void init_timer(unsigned int freq) {
    register_interrupt_handler(32, timer_callback);
    unsigned int divisor = 1193180 / freq;
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)( (divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36); 
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

unsigned int get_uptime() {
    return tick;
}

void sleep(unsigned int timer_ticks) {
    unsigned int start_ticks = tick;
    while(tick < start_ticks + timer_ticks) {
        __asm__ __volatile__("hlt"); 
    }
}
