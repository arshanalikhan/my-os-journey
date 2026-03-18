#include "libc.h"

void print(char *msg) {
    __asm__ __volatile__("int $0x80" : : "a"(1), "b"(msg));
}

void scan(char *buffer) {
    // EAX = 3 (Read String Syscall). EBX = Pointer to where to save the text.
    __asm__ __volatile__("int $0x80" : : "a"(3), "b"(buffer));
}
