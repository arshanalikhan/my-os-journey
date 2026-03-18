#include "keyboard.h"
#include "ports.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../kernel/string.h"

void execute_command(char *input);

static char key_buffer[256];

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_map[59] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0,
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' '
};

// FIX 1: Added 'volatile' so the compiler knows these change in the background!
volatile int waiting_for_app_input = 0;
volatile int app_input_ready = 0;

void keyboard_callback(registers_t *regs) {
    unsigned char scancode = port_byte_in(0x60);
    
    if (scancode > 57) return;

    if (scancode == BACKSPACE) {
        if (strlen(key_buffer) > 0) {
            backspace(key_buffer);
            kprint_backspace();
        }
    } 
    else if (scancode == ENTER) {
        kprint("\n");
        // If an app is waiting for input, just signal that we are done!
        if (waiting_for_app_input == 1) {
            waiting_for_app_input = 0;
            app_input_ready = 1;
        } 
        // Otherwise, run a normal shell command
        else {
            execute_command(key_buffer);
            key_buffer[0] = '\0';
        }
    } 
    else {
        char letter = key_map[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
}

// Syscall #3 calls this to pause the OS and wait for the user
void get_app_input(char *user_buffer) {
    key_buffer[0] = '\0'; // Clear the buffer
    app_input_ready = 0;
    waiting_for_app_input = 1; // Flip the switch!
    
    // FIX 2: Re-enable hardware interrupts! 
    // We are inside a Syscall, so interrupts are currently blocked. 
    // We MUST turn them back on so the keyboard can actually type!
    __asm__ __volatile__("sti");

    // Put the CPU to sleep until the user hits ENTER
    while (app_input_ready == 0) {
        __asm__ __volatile__("hlt");
    }
    
    // Copy the typed text straight into the User App's memory!
    strcpy(key_buffer, user_buffer);
    key_buffer[0] = '\0'; // Clean up
}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_callback); 
}
