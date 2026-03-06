# Day 19: User Mode (Ring 3 Security) 

Yesterday, every program had God Mode access to the hardware. Today, the OS built a sandbox

this required configuring the Task State Segment (TSS) and performing a fake interrupt return (iret) to trick the CPU into downgrading its privilege level

## what’s happening in the image:
* OS transitions execution to Ring 3 (User Mode)
* the user program attempts an illegal, privileged instruction (cli)
* the CPU's hardware security detects the violation and blocks it
* a General Protection Fault is thrown
* the Kernel safely catches the exception and terminates the thread instead of crashing the system

Just downgrade -> execute -> trap -> catch -> success

![day19](https://github.com/user-attachments/assets/6f3aaa0f-84f3-40a1-b841-4e1e8e990866)




