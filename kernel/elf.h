#ifndef ELF_H
#define ELF_H

#include "../drivers/types.h"

typedef struct {
    u8  e_ident[16];  
    u16 e_type;       
    u16 e_machine;    
    u32 e_version;
    u32 e_entry;      
    u32 e_phoff;      // OFFSET TO THE PROGRAM HEADERS!
    u32 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;      // HOW MANY PROGRAM HEADERS ARE THERE?
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} __attribute__((packed)) elf32_ehdr_t;

// --- DAY 22: ADD THIS NEW STRUCT ---
typedef struct {
    u32 p_type;       // 1 = Loadable Segment (We must load this into RAM)
    u32 p_offset;     // Where in the file is the data?
    u32 p_vaddr;      // What physical memory address does it want to go to?
    u32 p_paddr;
    u32 p_filesz;     // How many bytes to copy
    u32 p_memsz;
    u32 p_flags;
    u32 p_align;
} __attribute__((packed)) elf32_phdr_t;
// -----------------------------------

#endif
