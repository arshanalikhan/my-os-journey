Day 4 of building an OS from scratch (x86)
 
what i worked on:

* created a memory mapping system (GDT)
* it has 3 main segments - a safety requirement, executable code, data(variable)
* jumped from real mode (16 bit) to protected mode (32 bit)
* jumped from max ram 1 MB to 4 GB

today wasn't about adding new features; it was about taking full control of the hardware while keeping in if one program fails then OS will never crash
