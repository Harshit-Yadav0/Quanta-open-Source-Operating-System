#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "kernel.h"

/* ================= IDT ================= */

#define IDT_ENTRIES 256

typedef struct {
    u16 base_low;
    u16 selector;
    u8  zero;
    u8  flags;
    u16 base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_ptr_t;

/* ================= API ================= */

/* Initialize interrupts & timer */
void interrupts_init(void);

/* Timer tick counter */
u32 timer_get_ticks(void);

#endif /* INTERRUPTS_H */
