// kernel.c
// Minimal educational kernel foundation

#include "kernel.h"
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/* VGA text mode memory */
#define VGA_MEMORY 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static u16* vga_buffer = (u16*)VGA_MEMORY;
static u8 cursor_x = 0;
static u8 cursor_y = 0;

/* ================= LOW LEVEL OUTPUT ================= */

void vga_put_char(char c)
{
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    u16 index = cursor_y * VGA_WIDTH + cursor_x;
    vga_buffer[index] = (0x0F << 8) | c;

    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

void kprint(const char* str)
{
    while (*str) {
        vga_put_char(*str++);
    }
}

/* ================= KERNEL ENTRY ================= */

void kernel_main(void)
{
    kprint("SmartOS Kernel Starting...\n");
    kprint("Kernel is alive.\n");

    // Kernel idle loop
    while (1) {
        __asm__ volatile ("hlt");
    }
}
