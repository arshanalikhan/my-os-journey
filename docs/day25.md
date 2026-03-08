# Day 25: Giving Apps "Ears" (Interactive Syscalls)

Yesterday, I gave my Userland applications a voice, allowing them to print to the screen. But they couldn't listen. If I wanted to write a calculator or a password prompt, the apps had no way to receive keyboard input

today, I made Userland interactive

this required writing a new Syscall (Read String), modifying the hardware keyboard driver to route keystrokes directly into an isolated app's memory buffer, and carefully managing CPU sleep states to prevent interrupt deadlocks

## what’s happening in the image:
* the OS dynamically loads a standalone C program (APP.ELF) from the virtual disk
* the app asks the user for their name and triggers Syscall #3 (scan)
* the Kernel puts the app to sleep and listens to the hardware keyboard controller
* I type my name, and the Kernel safely injects those keystrokes into the isolated app's memory space
* the app wakes up, reads the variable, and prints a personalized response before gracefully exiting!

Just prompt -> trap to kernel -> listen to hardware -> inject memory -> wake app -> success

<img width="1544" height="1030" alt="Screenshot 2026-03-06 192751" src="https://github.com/user-attachments/assets/fd9801b5-7e54-4b7d-bc86-c00755765630" />
