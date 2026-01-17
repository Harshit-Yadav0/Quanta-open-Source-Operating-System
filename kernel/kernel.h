#ifndef KERNEL_H
#define KERNEL_H

/* ================= BASIC TYPES ================= */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     s32;

/* ================= KERNEL INFO ================= */

#define KERNEL_NAME    "SmartOS"
#define KERNEL_VERSION "0.1.0"

/* ================= VGA TEXT MODE ================= */

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/* ================= KERNEL CORE ================= */

/* Kernel entry point (called by bootloader) */
void kernel_main(void);

/* Low-level screen output */
void vga_put_char(char c);
void kprint(const char* str);

/* ================= CPU CONTROL ================= */

/* Halt CPU until next interrupt */
static inline void cpu_halt(void)
{
    __asm__ volatile ("hlt");
}

/* Disable interrupts */
static inline void disable_interrupts(void)
{
    __asm__ volatile ("cli");
}

/* Enable interrupts */
static inline void enable_interrupts(void)
{
    __asm__ volatile ("sti");
}

#endif /* KERNEL_H */
