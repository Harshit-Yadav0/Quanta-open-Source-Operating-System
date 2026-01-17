#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "kernel.h"
#include "memory_manager.h"

/* ================= PROCESS ================= */

#define MAX_PROCESSES 32

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING
} process_state_t;

typedef struct {
    u32 pid;
    u32 esp;
    u32 ebp;
    process_state_t state;
    u8  is_heavy;
} process_t;

/* ================= API ================= */

void scheduler_init(void);
u32  process_create(void (*entry)(), u8 heavy);
void scheduler_tick(void);

#endif /* SCHEDULER_H */
