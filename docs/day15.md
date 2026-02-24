# Day 15: The System Timer & Asynchronous I/O 

Yesterday, the OS had no concept of time and locked up while processing
Today, it tracks uptime and handles background tasks

this required programming the hardware PIT (Programmable Interval Timer) and decoupling keyboard interrupts from the main kernel loop

## what’s happening in the image:
* PIT hardware initialized to fire 100 times per second (Hz)
* UPTIME command calculates live seconds from raw CPU ticks
* SLEEP command halts the CPU (hlt) efficiently instead of busy-waiting
* Keyboard input buffers in the background while the OS sleeps (Async I/O!)
* Smart ISR correctly routes the CRASH test to a custom Page Fault handler

Just hardware timer -> interrupt -> background buffer -> execute -> success
<img width="1475" height="954" alt="Screenshot 2026-02-23 233603" src="https://github.com/user-attachments/assets/b47c2074-49a4-44fd-94ef-08e7187e611e" />
<img width="1447" height="935" alt="Screenshot 2026-02-24 014859" src="https://github.com/user-attachments/assets/fa7fb352-6f98-4f05-b308-2122fbc039a6" />
