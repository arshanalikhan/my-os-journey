Day 12: The Smart Shell

until yesterday, my shell could only understand single-word commands
if I typed something longer, it would break or ignore half of it

today, I taught the kernel how to actually parse input

* what action is being requested (WRITE)
* which file it applies to (ARSHAN.TXT)
* and what the actual content is (HI THIS IS ARSHAN'S OS)

to make that work, I built a small string parser in C
* get_arg() extracts individual words by skipping spaces
* get_tail() skips the command and filename, then captures everything else as a single block of text

now I can write full sentences to my file system and read them back correctly
it finally feels less like a demo… and more like an operating system

