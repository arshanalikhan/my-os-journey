[org 0x7c00]

mov [BOOT_DRIVE], dl ; Save the boot drive

mov bp, 0x9000       ; Set the stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call switch_to_pm    ; never return from here

jmp $

%include "gdt.asm"
%include "print_string.asm"    
%include "switch_to_pm.asm"
%include "print_string_pm.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm   ; 

    jmp $                  ; till here today

; Global variables
BOOT_DRIVE: db 0
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0

; Padding
times 510-($-$$) db 0
dw 0xaa55
