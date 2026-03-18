global gdt_flush
global tss_flush
global switch_to_user_mode

gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret

tss_flush:
    mov ax, 0x2B
    ltr ax
    ret

switch_to_user_mode:
    cli
    mov ax, 0x23      ; User Data Segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push 0x23         ; Push SS
    push eax          ; Push ESP
    pushf             ; Push EFLAGS
    pop eax
    or eax, 0x200     ; Re-enable interrupts
    push eax
    push 0x1B         ; Push CS (User Code Segment)
    push .user_mode   ; Push EIP
    iret              ; Jump to Ring 3!
.user_mode:
    ret
