// interrupts.c
// Basic interrupt & timer setup (x86)

#include "interrupts.h"

/* ================= INTERNAL ================= */

static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t   idt_ptr;

static volatile u32 timer_ticks = 0;

/* ================= LOW LEVEL ================= */

extern void idt_load(u32);

/* ================= IDT SETUP ================= */

static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
    idt[num].base_low  = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero     = 0;
    idt[num].flags    = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

/* ================= TIMER ================= */

void timer_handler(void)
{
    timer_ticks++;
}

/* ================= INIT ================= */

void interrupts_init(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base  = (u32)&idt;

    /* Clear IDT */
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    /* Timer interrupt (IRQ0 → INT 32) */
    idt_set_gate(32, (u32)timer_handler, 0x08, 0x8E);

    /* Load IDT */
    idt_load((u32)&idt_ptr);

    enable_interrupts();
}

/* ================= INFO ================= */

u32 timer_get_ticks(void)
{
    return timer_ticks;
}
