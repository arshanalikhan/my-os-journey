#include "vga.h"

void put_pixel(int x, int y, unsigned char color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        unsigned char *screen = (unsigned char *)VGA_ADDRESS;
        screen[(y * SCREEN_WIDTH) + x] = color;
    }
}

// --- NEW: Read a pixel from the screen! ---
unsigned char get_pixel(int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        unsigned char *screen = (unsigned char *)VGA_ADDRESS;
        return screen[(y * SCREEN_WIDTH) + x];
    }
    return 0; // Return black if out of bounds
}

void draw_rect(int x, int y, int width, int height, unsigned char color) {
    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width; j++) {
            put_pixel(j, i, color);
        }
    }
}

void fill_screen(unsigned char color) {
    unsigned char *screen = (unsigned char *)VGA_ADDRESS;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        screen[i] = color;
    }
}
