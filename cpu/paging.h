#ifndef PAGING_H
#define PAGING_H

#include "../cpu/isr.h"

// A Page Table Entry (32-bit)
typedef struct {
   unsigned int present    : 1;   // Page present in memory
   unsigned int rw         : 1;   // Read-only if clear, readwrite if set
   unsigned int user       : 1;   // Supervisor level only if clear
   unsigned int accessed   : 1;   // Has the page been accessed since last refresh?
   unsigned int dirty      : 1;   // Has the page been written to since last refresh?
   unsigned int unused     : 7;   // Amalgamation of unused and reserved bits
   unsigned int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

// A Page Table (Contains 1024 pages)
typedef struct {
   page_t pages[1024];
} page_table_t;

// A Page Directory (Contains 1024 pointers to Page Tables)
typedef struct {
   // Pointers to page tables (physical addresses)
   unsigned int tablesPhysical[1024]; 
   
   // Pointers to page table structs (virtual addresses)
   page_table_t *tables[1024]; 
   
   // The physical address of tablesPhysical (for loading into CR3)
   unsigned int physicalAddr;
} page_directory_t;

void init_paging();
extern void switch_page_directory(page_directory_t *dir); // <-- ADDED THIS

#endif
