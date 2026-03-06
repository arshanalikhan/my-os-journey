# Day 20: System Calls

Yesterday, we locked User Programs inside a Ring 3 sandbox so they couldn't crash the kernel. But that created a new problem: how do isolated programs actually do anything if they aren't allowed to touch the hardware?

today, I built a Syscall Interface (Interrupt 0x80)

this required creating an assembly stub to catch the interrupt, a C handler to parse the registers, and a secure API bridge.

## What’s happening in the image:
* a User Mode program wants to print text to the VGA screen
* it cannot do it directly (Ring 3 restriction)
* it places the "Print" command number into the EAX register and triggers int 0x80
* the Kernel (Ring 0) intercepts the request, safely executes the print command, and hands control back
* Result: a successful, secure handshake between User Space and Kernel Space!

Just load registers -> trap to kernel -> execute -> return -> success
![day20](https://github.com/user-attachments/assets/c53ffa1b-ef9e-4f1e-84c1-ffdc3ba1b32e)
