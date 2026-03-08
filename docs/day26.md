# Day 26: Entering the Matrix (VGA Graphics & Mode 13h) 

for the past 25 days, my Operating System has been trapped in a retro, text-only terminal. Today, I took complete control of the pixels

I transitioned the OS from VGA Text Mode to VGA Graphics Mode 13h

this required modifying the 16-bit bootloader to execute a BIOS interrupt (int 0x10, ax=0x0013) right before entering Protected Mode, and writing a brand new C driver to interface with the 0xA0000 memory boundary

## what’s happening in the image 1:
* the screen is now a blank canvas of 320x200 pixels supporting 256 colors 
* I wrote a memory-mapping driver to calculate exact X/Y coordinates: offset = (Y * 320) + X
* the Kernel pushes raw byte values (like 0x09 for Light Blue, 0x0E for Yellow) directly into physical video RAM
* Result: a completely mathematically drawn landscape using my custom draw_rect() and fill_screen() algorithms!

Just calculate offset -> map to video RAM -> push color byte -> render -> success

<img width="1384" height="1030" alt="Screenshot 2026-03-06 193609" src="https://github.com/user-attachments/assets/8a95edfb-64f9-43da-b407-e0e8a806e190" />
<img width="1384" height="1030" alt="Screenshot 2026-03-06 194733" src="https://github.com/user-attachments/assets/5b044b1a-bf9b-49d7-aa65-9cdee6938bb8" />
