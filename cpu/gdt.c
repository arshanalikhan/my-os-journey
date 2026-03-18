#include "gdt.h"
#include "../kernel/mem.h"

typedef unsigned int u32; typedef unsigned short u16; typedef unsigned char u8;

struct gdt_entry_struct {
    u16 limit_low; u16 base_low; u8 base_middle; u8 access; u8 granularity; u8 base_high;
} __attribute__((packed));

struct gdt_ptr_struct {
    u16 limit; u32 base;
} __attribute__((packed));

struct tss_entry_struct {
    u32 prev_tss; u32 esp0; u32 ss0; u32 esp1; u32 ss1; u32 esp2; u32 ss2;
    u32 cr3; u32 eip; u32 eflags; u32 eax; u32 ecx; u32 edx; u32 ebx;
    u32 esp; u32 ebp; u32 esi; u32 edi;
    u32 es; u32 cs; u32 ss; u32 ds; u32 fs; u32 gs;
    u32 ldt; u16 trap; u16 iomap_base;
} __attribute__((packed));

struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct   gdt_ptr;
struct tss_entry_struct tss_entry;

extern void gdt_flush(u32);
extern void tss_flush();

void gdt_set_gate(int num, u32 base, u32 limit, u8 access, u8 gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

void write_tss(int num, u16 ss0, u32 esp0) {
    u32 base = (u32) &tss_entry;
    u32 limit = sizeof(tss_entry);
    gdt_set_gate(num, base, limit, 0xE9, 0x00);
    memset((u8*)&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0  = ss0;
    tss_entry.esp0 = esp0;
    tss_entry.cs   = 0x0B;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
    tss_entry.iomap_base = sizeof(tss_entry);
}

void init_gdt() {
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
    gdt_ptr.base  = (u32)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // 0: Null
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // 1: Kernel Code
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 2: Kernel Data
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // 3: User Code (Ring 3)
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // 4: User Data (Ring 3)
    write_tss(5, 0x10, 0x90000);                // 5: TSS

    gdt_flush((u32)&gdt_ptr);
    tss_flush();
}
