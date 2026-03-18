#include "mem.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) *(dest + i) = *(source + i);
}
void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
void memset(u8 *dest, u8 val, u32 len) { memory_set(dest, val, len); }

// Old Placement Allocator
u32 free_mem_addr = 0x10000; 

u32 kmalloc_int(u32 size, int align, u32 *phys) {
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) { 
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    if (phys) *phys = free_mem_addr;
    u32 ret = free_mem_addr;
    free_mem_addr += size;
    return ret;
}

u32 kmalloc_a(u32 size) { return kmalloc_int(size, 1, 0); }
u32 kmalloc_p(u32 size, u32 *phys) { return kmalloc_int(size, 0, phys); }
u32 kmalloc_ap(u32 size, u32 *phys) { return kmalloc_int(size, 1, phys); }
u32 kmalloc(u32 size) { return kmalloc_int(size, 0, 0); }

// New Heap Allocator
typedef struct block_meta {
    u32 size;
    int is_free;
    struct block_meta *next;
} block_meta_t;

#define META_SIZE sizeof(block_meta_t)

void *global_base = 0;

void init_dynamic_mem() {
    if (free_mem_addr & 0xFFFFF000) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    global_base = 0; // FIX: Ensure this starts at 0 so malloc doesn't infinite loop!
}

block_meta_t *find_free_block(block_meta_t **last, u32 size) {
    block_meta_t *current = (block_meta_t *)global_base;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

block_meta_t *request_space(block_meta_t *last, u32 size) {
    block_meta_t *block = (block_meta_t *)free_mem_addr;
    free_mem_addr += META_SIZE + size; 
    block->size = size;
    block->is_free = 0;
    block->next = 0;
    if (last) last->next = block;
    return block;
}

void *malloc(u32 size) {
    block_meta_t *block;
    if (size <= 0) return 0;
    
    if (!global_base) { 
        block = request_space(0, size);
        global_base = block;
    } else {
        block_meta_t *last = (block_meta_t *)global_base;
        block = find_free_block(&last, size);
        if (!block) { 
            block = request_space(last, size);
        } else {      
            block->is_free = 0; 
        }
    }
    return (block + 1); 
}

void free(void *ptr) {
    if (!ptr) return;
    block_meta_t *block = (block_meta_t*)ptr - 1; 
    block->is_free = 1; 
}
