#include "mouse.h"
#include "ports.h"
#include "screen.h"
#include "../cpu/isr.h"

volatile int mouse_x = 160; 
volatile int mouse_y = 100;
// NEW: Global variable for the left mouse button!
volatile int mouse_click = 0; 

int mouse_cycle = 0;
signed char mouse_byte[3]; 

void mouse_wait(unsigned char a_type) {
    int timeout = 100000; 
    if (a_type == 0) {
        while (timeout--) { if ((port_byte_in(0x64) & 1) == 1) return; }
    } else {
        while (timeout--) { if ((port_byte_in(0x64) & 2) == 0) return; }
    }
}

void mouse_write(unsigned char a_write) {
    mouse_wait(1);
    port_byte_out(0x64, 0xD4);
    mouse_wait(1);
    port_byte_out(0x60, a_write);
}

unsigned char mouse_read() {
    mouse_wait(0);
    return port_byte_in(0x60);
}

void mouse_callback(registers_t *regs) {
    port_byte_out(0xA0, 0x20); 
    port_byte_out(0x20, 0x20); 

    unsigned char status = port_byte_in(0x64);
    unsigned char data = port_byte_in(0x60); 
    
    if (!(status & 0x20)) return;
    if (mouse_cycle == 0 && !(data & 0x08)) return;

    mouse_byte[mouse_cycle++] = data;

    if (mouse_cycle == 3) {
        mouse_cycle = 0;
        
        // --- THE CLICK UPGRADE ---
        // Bit 0 of the first byte is the Left Mouse Button!
        mouse_click = mouse_byte[0] & 0x01; 
        
        mouse_x += mouse_byte[1];
        mouse_y -= mouse_byte[2];

        if (mouse_x < 0) mouse_x = 0;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_x > 309) mouse_x = 309; 
        if (mouse_y > 184) mouse_y = 184; 
    }
}

void init_mouse() {
    // ... (Keep your existing init_mouse code exactly the same) ...
    unsigned char status;
    mouse_wait(1); port_byte_out(0x64, 0xA8);
    mouse_wait(1); port_byte_out(0x64, 0x20);
    mouse_wait(0); status = (port_byte_in(0x60) | 2);
    mouse_wait(1); port_byte_out(0x64, 0x60);
    mouse_wait(1); port_byte_out(0x60, status);
    mouse_write(0xF6); mouse_read(); 
    mouse_write(0xF4); mouse_read(); 
    register_interrupt_handler(44, mouse_callback);
}
