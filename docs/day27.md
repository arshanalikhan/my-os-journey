# Day 27: The Font Renderer (Typography in the Matrix) 

Yesterday, I switched my OS into VGA Graphics Mode (320x200 pixels). I gained infinite visual freedom but lost my interactive text shell, because the hardware no longer draws ASCII characters for me

Today, I built a custom Font Renderer to get my voice back

this required importing a raw 8x8 Bitmap Font array and writing a C driver to translate raw binary bits into X/Y pixel coordinates on the screen

## what’s happening in the image:
* the OS paints the background scene using primitive shape algorithms (draw_rect, fill_screen)
* the kprint_gui function reads my custom text strings
* it loops through the 8x8 binary grid for each specific character 
* using bitwise operations, it checks if a bit is 1 (paint the pixel) or 0 (skip it)
* Result: flawless, custom-colored typography rendered pixel-by-pixel directly on top of the graphical canvas!

Just map font -> read bits -> calculate offset -> paint pixel -> success

<img width="1384" height="1030" alt="Screenshot 2026-03-07 163928" src="https://github.com/user-attachments/assets/9d5d4360-3182-45c1-bc77-9e4f6d12a0f7" />
