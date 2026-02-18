# Day 9: The Shell (x86)

Until yesterday, my OS could listen
Today, it actually understands

Before this, I could type on the keyboard and see characters appear on the screen
But the kernel had zero memory. Every keypress was just printed and forgotten

For the first time, the OS now stores what I type inside a buffer:

--> static char key_buffer[256];

Now when I type:
H → it prints to screen
H → it also stores it in memory

Same for E, L, P…
And when I press ENTER, the kernel doesn’t just move to a new line
It analyzes what I typed

## Since this is bare metal, there’s no <string.h>
So I had to write my own:
* strcmp() to compare commands
* append() to build strings

## Then I built a tiny command parser:
* HELP -> shows menu
* PAGE -> request a physical page
* CLEAR -> clears screen
* anything else -> “Unknown command”

This is basically my first REPL:
Read -> Evaluate -> Print -> Loop

It’s starting to feel like a real operating system
<img width="2879" height="1799" alt="Screenshot 2026-02-15 234937" src="https://github.com/user-attachments/assets/fb7ff1bf-4ecc-4999-9f5d-a5a33e6a47a4" />

