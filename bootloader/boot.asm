#arshan

[org 0x7c00]

mov ah, 0x0e

mov al, 'A'
int 0x10
mov al, 'R'
int 0x10
mov al, 'S'
int 0x10
mov al, 'H'
int 0x10
mov al, 'A'
int 0x10
mov al, 'N'
int 0x10

jmp $

times 510-($-$$) db 0
dw 0xaa55



#hello this is arshan's os!

[org 0x7c00]

mov si, message

print:
    lodsb
    cmp al, 0
    je done
    mov ah, 0x0e
    int 0x10
    jmp print

done:
    jmp $

message db "Hello, this is Arshan's OS!", 0

times 510-($-$$) db 0
dw 0xaa55





#disk loader function

[org 0x7c00]

mov [BOOT_DRIVE], dl ; 1. BIOS stores the boot drive number in DL. Save it.

mov bp, 0x8000       ; 2. Set the stack safely away from our code
mov sp, bp

mov bx, 0x9000       ; 3. Load 5 sectors to memory address 0x9000
mov dh, 1            ; (Read 1 sector)
mov dl, [BOOT_DRIVE]
call disk_load

mov bx, 0x9000       ; 4. Jump to the address where we loaded the kernel
jmp bx

jmp $

; --- DISK LOAD FUNCTION ---
disk_load:
    push dx          ; Store DX on stack so we can check it later

    mov ah, 0x02     ; BIOS read sector function
    mov al, dh       ; Read DH sectors
    mov ch, 0x00     ; Select Cylinder 0
    mov dh, 0x00     ; Select Head 0
    mov cl, 0x02     ; Start reading from Sector 2 (Sector 1 is bootloader)
    
    int 0x13         ; BIOS interrupt

    jc disk_error    ; "Jump Carry". If error, BIOS sets Carry Flag.

    pop dx           ; Restore DX from the stack
    cmp dh, al       ; BIOS sets AL to # of sectors actually read
    jne disk_error   ; If AL != DH (sectors requested), error!
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

; --- PRINT STRING FUNCTION (From Day 2) ---
print_string:
    pusha
    mov ah, 0x0e
.loop:
    mov al, [bx]
    cmp al, 0
    je .done
    int 0x10
    inc bx
    jmp .loop
.done:
    popa
    ret

; --- DATA ---
BOOT_DRIVE: db 0
DISK_ERROR_MSG: db "Disk read error!", 0

times 510-($-$$) db 0
dw 0xaa55
