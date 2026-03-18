#ifndef MEM_H
#define MEM_H

#include "../cpu/isr.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);
void memset(u8 *dest, u8 val, u32 len);

// Old Placement Allocator (Used by Paging internally)
u32 kmalloc(u32 size);
u32 kmalloc_a(u32 size); 
u32 kmalloc_p(u32 size, u32 *phys); 
u32 kmalloc_ap(u32 size, u32 *phys); 

// NEW: The Real Heap Allocator
void init_dynamic_mem();
void *malloc(u32 size);
void free(void *ptr);

#endif
