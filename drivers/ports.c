// drivers/ports.c

// Read a byte from the specified port
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    // "=a" (result) means: put AL register in variable result when finished
    // "d" (port) means: load EDX with port
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    // "a" (data) means: load EAX with data
    // "d" (port) means: load EDX with port
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
