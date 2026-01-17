#ifndef CONTEXT_SWITCH_H
#define CONTEXT_SWITCH_H

#include "kernel.h"
#include "scheduler.h"

/* Switch from old process to new process */
void context_switch(process_t* old, process_t* new);

#endif
