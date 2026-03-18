[org 0x7c00]
KERNEL_OFFSET equ 0x8000

    mov [BOOT_DRIVE], dl
    mov bp, 0x7c00
    mov sp, bp

    call load_kernel
    
    ; --- DAY 26: ENTER VGA GRAPHICS MODE 13h ---
    mov ah, 0x00    ; Set video mode function
    mov al, 0x13    ; Mode 13h (320x200, 256 colors)
    int 0x10        ; Tell the BIOS to flip the switch!
    ; -------------------------------------------

    call switch_to_pm
    jmp $

load_kernel:
    mov ah, 0x42
    mov dl, [BOOT_DRIVE]
    mov si, dap
    int 0x13
    ret

[bits 16]
switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_pm

BOOT_DRIVE db 0

align 4
dap:
    db 0x10
    db 0
    dw 100             
    dw KERNEL_OFFSET
    dw 0x0000
    dq 1

gdt_start:
    dq 0x0
gdt_code:
    dw 0xffff, 0x0
    db 0x0, 10011010b, 11001111b, 0x0
gdt_data:
    dw 0xffff, 0x0
    db 0x0, 10010010b, 11001111b, 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    call KERNEL_OFFSET
    jmp $

times 510-($-$$) db 0
dw 0xaa55
