#include "screen.h"
#include "ports.h"
#include "../kernel/mem.h"
#include "../kernel/string.h"

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// --- Private Helper Functions ---
int get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) { 
    return 2 * (row * MAX_COLS + col); 
}

int get_offset_row(int offset) { 
    return offset / (2 * MAX_COLS); 
}

// --- Main Screen Functions ---

// UPDATED: Now accepts 'attribute' for color
void kprint_at(char *message, int col, int row, char attribute) {
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = (offset - (row * 2 * MAX_COLS)) / 2;
    }

    int i = 0;
    while (message[i] != 0) {
        offset = get_cursor_offset();
        
        if (message[i] == '\n') {
            row = get_offset_row(offset);
            offset = get_offset(0, row + 1);
        } else {
            char *vidmem = (char*) VIDEO_ADDRESS;
            vidmem[offset] = message[i];
            vidmem[offset+1] = attribute; // <--- USE CUSTOM COLOR HERE
            offset += 2;
        }

        // Check if we hit the bottom of the screen
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            int i;
            for (i = 1; i < MAX_ROWS; i++) 
                memcpy((char*)get_offset(0, i) + VIDEO_ADDRESS,
                       (char*)get_offset(0, i-1) + VIDEO_ADDRESS,
                       MAX_COLS * 2);

            // Blank last line
            char *last_line = (char*) (get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS);
            for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

            offset -= 2 * MAX_COLS;
        }

        set_cursor_offset(offset);
        i++;
    }
}

// Default print (White on Black)
void kprint(char *message) {
    kprint_at(message, -1, -1, WHITE_ON_BLACK);
}

// NEW: Color print wrapper
void kprint_color(char *message, char color) {
    kprint_at(message, -1, -1, color);
}

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    int row = offset / (2 * MAX_COLS);
    int col = (offset - (row * 2 * MAX_COLS)) / 2;

    if (col >= 0) {
        kprint_at(" ", col, row, WHITE_ON_BLACK); 
        set_cursor_offset(offset);
    }
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    char *screen = (char*) VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}
