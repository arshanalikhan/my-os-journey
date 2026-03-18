#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// --- VGA COLORS ---
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xa
#define LIGHT_CYAN 0xb
#define LIGHT_RED 0xc
#define LIGHT_MAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define GREEN_ON_BLACK 0x02

// Function Prototypes
void clear_screen();
void kprint_at(char *message, int col, int row, char attribute);
void kprint(char *message);
void kprint_color(char *message, char color);
void kprint_backspace();

#endif
