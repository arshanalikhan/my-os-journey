#ifndef TASK_H
#define TASK_H

#include "../drivers/types.h"

// The Task Control Block
typedef struct thread {
    u32 esp;              // The saved stack pointer
    struct thread* next;  // Pointer to the next task in the queue
} thread_t;

void thread_init();
thread_t* thread_create(void (*function)());
void thread_yield();

#endif
