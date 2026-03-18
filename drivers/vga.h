#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

void put_pixel(int x, int y, unsigned char color);
unsigned char get_pixel(int x, int y); // <--- NEW FUNCTION
void draw_rect(int x, int y, int width, int height, unsigned char color);
void fill_screen(unsigned char color);

#endif
