// context_switch.c
// C wrapper for low-level context switch

#include "context_switch.h"

/* Assembly function */
extern void context_switch_asm(u32* old_esp, u32* new_esp);

void context_switch(process_t* old, process_t* new)
{
    if (old == new)
        return;

    context_switch_asm(&old->esp, &new->esp);
}
