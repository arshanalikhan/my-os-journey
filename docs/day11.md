# Day 11: The File System (RamFS) - The OS Now Remembers (x86)

Until yesterday, my OS could execute, allocate memory, and respond to commands
but everything lived in temporary memory only

today, it can store and retrieve structured data
this took designing a small in-memory file system (RamFS) from scratch.

I implemented a simple file table with metadata (name, size, pointer) and connected it to my shell commands.

## what’s happening in the screenshot:
* file system initialized inside RAM
* WRITE command creates a file (secret.txt)
* LS confirms the file exists
* CAT reads the stored data back

that means:
write -> allocate -> index -> retrieve -> success

Still volatile (RAM-based), but this is the first step toward persistent storage.

<img width="2879" height="1799" alt="day11" src="https://github.com/user-attachments/assets/ccb584ca-0f42-41e7-b741-70560eb519b1" />
