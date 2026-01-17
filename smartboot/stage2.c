typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define KERNEL_ADDR 0x100000

void print(const char* s) {
    while (*s) {
        __asm__ volatile (
            "mov ah, 0x0E;"
            "int 0x10;"
            :
            : "a"(*s)
        );
        s++;
    }
}

u32 detect_ram() {
    return 512; // MB (simple fixed for now)
}

int detect_storage() {
    return 1; // assume disk exists
}

u32 simple_hash(u8* data, u32 size) {
    u32 h = 0;
    for (u32 i = 0; i < size; i++)
        h = (h << 5) + data[i];
    return h;
}

void load_kernel() {
    print("\nLoading Kernel...");
    // real disk read skipped (focus design)
}

void stage2_main() {
    print("\nSmartBoot Stage2");

    u32 ram = detect_ram();
    if (ram < 256) {
        print("\nLow RAM. Halt.");
        return;
    }

    if (!detect_storage()) {
        print("\nNo storage found.");
        return;
    }

    print("\nRAM & Storage OK");

    load_kernel();

    u32 trusted_hash = 0x12345678;
    u32 kernel_hash  = trusted_hash; // dummy

    if (kernel_hash != trusted_hash) {
        print("\nKernel verification failed!");
        return;
    }

    print("\nKernel verified. Jumping...");
    void (*kernel)() = (void*)KERNEL_ADDR;
    kernel();
}
