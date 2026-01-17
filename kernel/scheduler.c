// scheduler.c
// Very basic round-robin scheduler (educational)

#include "scheduler.h"

/* ================= INTERNAL ================= */

static process_t processes[MAX_PROCESSES];
static u32 process_count = 0;
static u32 current_process = 0;

/* ================= INIT ================= */

void scheduler_init(void)
{
    for (u32 i = 0; i < MAX_PROCESSES; i++) {
        processes[i].state = PROCESS_WAITING;
    }
}

/* ================= PROCESS CREATE ================= */

u32 process_create(void (*entry)(), u8 heavy)
{
    if (process_count >= MAX_PROCESSES)
        return (u32)-1;

    process_t* p = &processes[process_count];

    /* Allocate stack (4 KB) */
    void* stack = memory_alloc(4096, heavy);
    if (!stack)
        return (u32)-1;

    u32 stack_top = (u32)stack + 4096;

    p->pid   = process_count;
    p->esp   = stack_top;
    p->ebp   = stack_top;
    p->state = PROCESS_READY;
    p->is_heavy = heavy;

    process_count++;
    return p->pid;
}

/* ================= SCHEDULER ================= */

/*
 Called on every timer interrupt (future)
*/
void scheduler_tick(void)
{
    if (process_count == 0)
        return;

    processes[current_process].state = PROCESS_READY;

    current_process = (current_process + 1) % process_count;

    processes[current_process].state = PROCESS_RUNNING;

    /* Context switch will be added later */
}
