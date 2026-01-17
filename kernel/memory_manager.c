// memory_manager.c
// Basic RAM manager with 1:2:2 policy
// Contributor-friendly & kernel-safe

#include "memory_manager.h"

/* ================= INTERNAL STATE ================= */

static memory_layout_t mem_layout;

/* Simple linear allocators for each pool */
static u32 os_current;
static u32 normal_current;
static u32 heavy_current;

/* ================= INITIALIZATION ================= */

void memory_init(u32 total_ram_bytes)
{
    mem_layout.total_ram = total_ram_bytes;

    /* Divide RAM into 5 equal parts */
    u32 part_size = total_ram_bytes / TOTAL_RAM_PARTS;

    mem_layout.os_reserved  = part_size * OS_RAM_PARTS;
    mem_layout.normal_pool = part_size * NORMAL_RAM_PARTS;
    mem_layout.heavy_pool  = part_size * HEAVY_RAM_PARTS;

    /* Define pool start addresses (simple layout) */
    os_current     = 0x100000; /* 1 MB mark (safe kernel area) */
    normal_current = os_current + mem_layout.os_reserved;
    heavy_current  = normal_current + mem_layout.normal_pool;
}

/* ================= ALLOCATION ================= */

/*
 heavy_app = 0 → normal app
 heavy_app = 1 → heavy app
*/
void* memory_alloc(u32 size, u8 heavy_app)
{
    void* addr = 0;

    if (heavy_app) {
        if (heavy_current + size <=
            (normal_current + mem_layout.normal_pool + mem_layout.heavy_pool)) {

            addr = (void*)heavy_current;
            heavy_current += size;
        }
    } else {
        if (normal_current + size <=
            (os_current + mem_layout.os_reserved + mem_layout.normal_pool)) {

            addr = (void*)normal_current;
            normal_current += size;
        }
    }

    return addr; /* NULL if allocation failed */
}

/* ================= FREE (PLACEHOLDER) ================= */

/*
 NOTE:
 This kernel uses a simple bump allocator.
 memory_free is reserved for future implementation
 (linked list / bitmap based allocator).
*/
void memory_free(void* ptr)
{
    (void)ptr; /* unused for now */
}

/* ================= INFO ================= */

memory_layout_t memory_get_layout(void)
{
    return mem_layout;
}
