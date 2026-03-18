#include "paging.h"
#include "../kernel/mem.h"
#include "../drivers/screen.h"
#include "../kernel/string.h"

unsigned int *frames;
unsigned int nframes;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

void set_frame(unsigned int frame_addr) {
   unsigned int frame = frame_addr / 0x1000;
   unsigned int idx = INDEX_FROM_BIT(frame);
   unsigned int off = OFFSET_FROM_BIT(frame);
   frames[idx] |= (0x1 << off);
}

int test_frame(unsigned int frame_addr) {
   unsigned int frame = frame_addr / 0x1000;
   unsigned int idx = INDEX_FROM_BIT(frame);
   unsigned int off = OFFSET_FROM_BIT(frame);
   return (frames[idx] & (0x1 << off));
}

unsigned int first_frame() {
   unsigned int i, j;
   for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
       if (frames[i] != 0xFFFFFFFF) {
           for (j = 0; j < 32; j++) {
               unsigned int toTest = 0x1 << j;
               if (!(frames[i] & toTest)) {
                   return i*4*8 + j;
               }
           }
       }
   }
   return (unsigned int)-1;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
   if (page->frame != 0) {
       return;
   } else {
       unsigned int idx = first_frame();
       if (idx == (unsigned int)-1) {
           kprint("Error: No free frames!\n");
           while(1);
       }
       set_frame(idx * 0x1000);
       page->present = 1;
       page->rw = (is_writeable) ? 1 : 0;
       page->user = (is_kernel) ? 0 : 1;
       page->frame = idx;
   }
}

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

page_t *get_page(unsigned int address, int make, page_directory_t *dir) {
   address /= 0x1000;
   unsigned int table_idx = address / 1024;
   
   if (dir->tables[table_idx]) {
       return &dir->tables[table_idx]->pages[address % 1024];
   } else if (make) {
       unsigned int tmp;
       dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
       memset((unsigned char*)dir->tables[table_idx], 0, 0x1000);
       dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US
       return &dir->tables[table_idx]->pages[address % 1024];
   } else {
       return 0;
   }
}

void page_fault(registers_t *regs) {
   unsigned int faulting_address;
   __asm__ __volatile__("mov %%cr2, %0" : "=r" (faulting_address));

   kprint_color("\nPAGE FAULT! ", RED);
   kprint("Address accessed illegally.\n");
   while(1);
}

// FIX: Inline Assembly to safely set CR3
void switch_page_directory(page_directory_t *dir) {
    current_directory = dir;
    __asm__ __volatile__("mov %0, %%cr3":: "r"((unsigned int)dir->tablesPhysical));
    unsigned int cr0;
    __asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable Paging bit
    __asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));
}

void init_paging() {
   unsigned int mem_end_page = 0x1000000; // 16MB
   
   nframes = mem_end_page / 0x1000;
   frames = (unsigned int*)kmalloc(INDEX_FROM_BIT(nframes));
   memset((unsigned char*)frames, 0, INDEX_FROM_BIT(nframes));

   kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
   memset((unsigned char*)kernel_directory, 0, sizeof(page_directory_t));
   current_directory = kernel_directory;

   // Map the first 4MB exactly as they are (Identity mapping)
   int i = 0;
   while (i < 0x400000) { 
       alloc_frame(get_page(i, 1, kernel_directory), 0, 1);
       i += 0x1000;
   }

   register_interrupt_handler(14, page_fault);

   // Turn on the Invisible Shield!
   switch_page_directory(kernel_directory);
}
