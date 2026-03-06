# Day 18: Preemptive Multitasking

Yesterday, programs had to politely share the CPU. If one froze, the whole OS died
Today, the OS takes control by force

this required wiring the context switcher directly into the hardware timer interrupt and escaping the dreaded "Interrupt Trap"

## what’s happening in the image:
* two "greedy" programs are running infinite loops, refusing to yield
* the Programmable Interval Timer (PIT) ticks in the background
* every 5 ticks, the hardware violently pauses the active program
* CPU registers are saved, stacks are swapped, and the next program is forced to run
* Result: chunks of green 'A's and red 'B's alternating automatically!

Just tick -> trap -> save state -> force swap -> success

![day18](https://github.com/user-attachments/assets/c7467fcb-5fcb-4aea-8803-60bca92e94d3)







