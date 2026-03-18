#include "gui_text.h"
#include "vga.h"
#include "font.h"

// Draws a single character pixel-by-pixel
void draw_char(char c, int x, int y, unsigned char color) {
    // Safety check: Ensure the character exists in our font array (ASCII 32 to 126)
    if (c < 32 || c > 126) return; 

    // Find the letter in our array (Subtract 32 because our array starts at Space)
    const unsigned char *glyph = font8x8[c - 32];

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Bitwise magic: Check if the specific bit at 'col' is a 1
            // We use 0x80 (10000000 in binary) and shift it right to read left-to-right!
            if (glyph[row] & (0x80 >> col)) {
                put_pixel(x + col, y + row, color);
            }
        }
    }
}

// Draws a full string by moving the X coordinate forward for each letter
void kprint_gui(char *str, int start_x, int start_y, unsigned char color) {
    int cursor_x = start_x;
    int cursor_y = start_y;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\n') {
            cursor_x = start_x;
            cursor_y += 10; // Move down a line (8px letter + 2px padding)
        } else {
            draw_char(str[i], cursor_x, cursor_y, color);
            cursor_x += 8; // Move cursor right for the next letter
        }
        i++;
    }
}
