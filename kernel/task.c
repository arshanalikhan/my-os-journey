#include "task.h"
#include "mem.h"

extern void switch_thread(u32 *old_esp_ptr, u32 new_esp);

thread_t *current_thread;
thread_t *main_thread;

void thread_init() {
    // Turn the main kernel execution into our first "Thread"
    main_thread = (thread_t*)malloc(sizeof(thread_t));
    main_thread->next = main_thread; // Circular linked list
    current_thread = main_thread;
}

thread_t* thread_create(void (*function)()) {
    // 1. Allocate memory for the task info
    thread_t *t = (thread_t*)malloc(sizeof(thread_t));
    
    // 2. Allocate a 4KB Stack for this specific task
    u32 *stack = (u32*)malloc(4096); 
    u32 *top_of_stack = (u32*)((u32)stack + 4096); // Stacks grow downwards

    // 3. Prepare the stack to look like it was paused by switch_thread
    *(--top_of_stack) = (u32)function; // EIP: Where the CPU will jump to
    *(--top_of_stack) = 0; // EBP
    *(--top_of_stack) = 0; // EDI
    *(--top_of_stack) = 0; // ESI
    *(--top_of_stack) = 0; // EBX

    t->esp = (u32)top_of_stack;
    
    // 4. Add it to our task queue
    t->next = current_thread->next;
    current_thread->next = t;

    return t;
}

void thread_yield() {
    // Stop current thread, pick the next one, and switch!
    thread_t *old = current_thread;
    current_thread = current_thread->next;
    switch_thread(&old->esp, current_thread->esp);
}
