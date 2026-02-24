Day 15: The System Timer & Asynchronous I/O 

Yesterday, the OS had no concept of time and locked up while processing
Today, it tracks uptime and handles background tasks

this required programming the hardware PIT (Programmable Interval Timer) and decoupling keyboard interrupts from the main kernel loop

what’s happening in the image:
* PIT hardware initialized to fire 100 times per second (Hz)
* UPTIME command calculates live seconds from raw CPU ticks
* SLEEP command halts the CPU (hlt) efficiently instead of busy-waiting
* Keyboard input buffers in the background while the OS sleeps (Async I/O!)
* Smart ISR correctly routes the CRASH test to a custom Page Fault handler

Just hardware timer -> interrupt -> background buffer -> execute -> success
