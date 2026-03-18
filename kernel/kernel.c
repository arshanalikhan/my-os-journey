#include "../cpu/isr.h"
#include "../drivers/vga.h" 
#include "../drivers/keyboard.h"
#include "../drivers/mouse.h" 
#include "../drivers/ports.h"
#include "../drivers/timer.h"
#include "../cpu/paging.h"
#include "../cpu/gdt.h"
#include "../drivers/gui_text.h"

extern volatile int mouse_x;
extern volatile int mouse_y;
extern volatile int mouse_click; // Import our new click variable!

int old_mouse_x = 160;
int old_mouse_y = 100;

int scheduler_running = 0;
void execute_command(char *input) { }

// --- DAY 30: THE WINDOW STRUCT ---
typedef struct {
    int x, y;
    int width, height;
    int is_dragging;
    int drag_offset_x;
    int drag_offset_y;
} Window;

// Create our first application window!
Window app_win = {50, 50, 160, 80, 0, 0, 0};

void draw_window(Window *win) {
    // 1. Draw Window Body (Light Grey)
    draw_rect(win->x, win->y, win->width, win->height, COLOR_LIGHT_GREY);
    
    // 2. Draw Title Bar (Dark Blue, 12 pixels tall)
    draw_rect(win->x, win->y, win->width, 12, COLOR_BLACK);
    
    // 3. Draw Title Text
    kprint_gui("DRAG ME!", win->x + 4, win->y + 2, COLOR_WHITE);
}

const char cursor_bitmap[15][10] = {
    {1,1,0,0,0,0,0,0,0,0},
    {1,2,1,0,0,0,0,0,0,0},
    {1,2,2,1,0,0,0,0,0,0},
    {1,2,2,2,1,0,0,0,0,0},
    {1,2,2,2,2,1,0,0,0,0},
    {1,2,2,2,2,2,1,0,0,0},
    {1,2,2,2,2,2,2,1,0,0},
    {1,2,2,2,2,2,2,2,1,0},
    {1,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,1,1,1},
    {1,2,2,1,1,2,2,1,0,0},
    {1,2,1,0,1,2,2,1,0,0},
    {1,1,0,0,0,1,2,2,1,0},
    {0,0,0,0,0,1,2,2,1,0},
    {0,0,0,0,0,0,1,1,0,0}
};

unsigned char bg_buffer[15][10];

void main() {
    init_gdt();      
    isr_install();   
    irq_install();   
    init_paging();   
    init_timer(50);  
    init_keyboard(); 
    init_mouse(); 
    
    __asm__ __volatile__("sti"); 

    // Initial Desktop Background
    fill_screen(COLOR_LIGHT_BLUE);
    draw_window(&app_win);

    for(int r=0; r<15; r++) {
        for(int c=0; c<10; c++) {
            bg_buffer[r][c] = get_pixel(mouse_x + c, mouse_y + r);
        }
    }

    // Draw initial cursor
    for(int r=0; r<15; r++) {
        for(int c=0; c<10; c++) {
            if (cursor_bitmap[r][c] == 1) put_pixel(mouse_x + c, mouse_y + r, COLOR_BLACK);
            else if (cursor_bitmap[r][c] == 2) put_pixel(mouse_x + c, mouse_y + r, COLOR_WHITE);
        }
    }

    while(1) { 
        // --- DRAG LOGIC ---
        // If we click down, check if we are inside the Title Bar (x to x+width, y to y+12)
        if (mouse_click == 1 && app_win.is_dragging == 0) {
            if (mouse_x >= app_win.x && mouse_x <= app_win.x + app_win.width &&
                mouse_y >= app_win.y && mouse_y <= app_win.y + 12) {
                
                app_win.is_dragging = 1;
                app_win.drag_offset_x = mouse_x - app_win.x;
                app_win.drag_offset_y = mouse_y - app_win.y;
            }
        }
        
        // If we release the mouse, stop dragging
        if (mouse_click == 0) {
            app_win.is_dragging = 0;
        }

        // --- RENDER CYCLE ---
        if (mouse_x != old_mouse_x || mouse_y != old_mouse_y || app_win.is_dragging) {
            
            // 1. Erase Cursor
            for(int r=0; r<15; r++) {
                for(int c=0; c<10; c++) {
                    put_pixel(old_mouse_x + c, old_mouse_y + r, bg_buffer[r][c]);
                }
            }

            // 2. If dragging, update window position and redraw the whole screen!
            if (app_win.is_dragging) {
                app_win.x = mouse_x - app_win.drag_offset_x;
                app_win.y = mouse_y - app_win.drag_offset_y;
                
                // Redraw Desktop & Window at new location
                fill_screen(COLOR_LIGHT_BLUE);
                draw_window(&app_win);
            }

            // 3. Save new background
            for(int r=0; r<15; r++) {
                for(int c=0; c<10; c++) {
                    bg_buffer[r][c] = get_pixel(mouse_x + c, mouse_y + r);
                }
            }

            // 4. Draw new Cursor
            for(int r=0; r<15; r++) {
                for(int c=0; c<10; c++) {
                    if (cursor_bitmap[r][c] == 1) put_pixel(mouse_x + c, mouse_y + r, COLOR_BLACK);
                    else if (cursor_bitmap[r][c] == 2) put_pixel(mouse_x + c, mouse_y + r, COLOR_WHITE);
                }
            }

            old_mouse_x = mouse_x;
            old_mouse_y = mouse_y;
        }
        
        __asm__ __volatile__("hlt"); 
    }
}
