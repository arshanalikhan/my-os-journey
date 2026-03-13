# Day 28: Hardware Integration (Building MS Paint!)

Yesterday, I gave my OS a voice with a Font Renderer. Today, I gave it a hand

I successfully wrote a hardware driver for the PS/2 Mouse and built a primitive version of MS Paint directly into the Kernel!

this required communicating with the PS/2 controller on Port 0x64, configuring the mouse to send data packets, and catching IRQ 12 (Interrupt 44) to process real-time movement

## what’s happening in the image:
* I click into the OS to bind my physical mouse
* the mouse hardware generates a 3-byte packet (Status, X movement, Y movement) every time I move my hand
* the Kernel catches the interrupt, synchronizes the packet, and updates a global X/Y coordinate
* a continuous while(1) loop reads those coordinates and paints a 3x3 white square on the VGA canvas
* because I am not "erasing" the previous position, the cursor leaves a permanent trail, turning the screen into a digital canvas!

Just initialize hardware -> catch interrupt -> sync packet -> calculate offset -> paint -> success

<img width="512" height="381" alt="day28" src="https://github.com/user-attachments/assets/577bb801-11af-4269-81a4-34f6a36bc57f" />
