# Day 4 of building an OS from scratch (x86)
 
## what i worked on:

* created a memory mapping system (GDT)
* it has 3 main segments - a safety requirement, executable code, data(variable)
* jumped from real mode (16 bit) to protected mode (32 bit)
* jumped from max ram 1 MB to 4 GB

today wasn't about adding new features; it was about taking full control of the hardware while keeping in if one program fails then OS will never crash
<img width="2352" height="1171" alt="Screenshot 2026-02-04 222942" src="https://github.com/user-attachments/assets/8c249f0e-050c-4978-80f3-95b7c2679de9" />
