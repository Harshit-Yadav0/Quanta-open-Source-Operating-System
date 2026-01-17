#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "kernel.h"

/* ================= MEMORY CONSTANTS ================= */

/*
 RAM usage policy (tumhari design):
 Total RAM = 5 parts
 1/5 -> OS (highest priority)
 2/5 -> Normal applications
 2/5 -> Heavy applications
*/

#define OS_RAM_PARTS      1
#define NORMAL_RAM_PARTS  2
#define HEAVY_RAM_PARTS   2
#define TOTAL_RAM_PARTS   5

/* ================= MEMORY STRUCTURES ================= */

/* Basic memory block info */
typedef struct {
    u32 start;
    u32 size;
    u8  used;
} mem_block_t;

/* Overall memory layout */
typedef struct {
    u32 total_ram;
    u32 os_reserved;
    u32 normal_pool;
    u32 heavy_pool;
} memory_layout_t;

/* ================= MEMORY API ================= */

/* Initialize memory manager (called once by kernel) */
void memory_init(u32 total_ram_bytes);

/* Allocate memory for a process */
void* memory_alloc(u32 size, u8 heavy_app);

/* Free allocated memory */
void memory_free(void* ptr);

/* Debug / info */
memory_layout_t memory_get_layout(void);

#endif /* MEMORY_MANAGER_H */
