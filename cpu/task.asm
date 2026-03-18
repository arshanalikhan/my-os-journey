global switch_thread

; void switch_thread(u32 *old_esp_ptr, u32 new_esp);
switch_thread:
    ; 1. Save current task's registers
    push ebx
    push esi
    push edi
    push ebp

    ; 2. Save the current Stack Pointer (ESP) into the old task's struct
    mov eax, [esp+20] ; Get pointer to old_esp from arguments
    mov [eax], esp    ; Save current ESP there

    ; 3. Load the new task's Stack Pointer (ESP)
    mov esp, [esp+24] ; Load new_esp from arguments

    ; 4. Restore the new task's registers
    pop ebp
    pop edi
    pop esi
    pop ebx
    
    ; 5. Jump into the new task!
    ret
