[BITS 16]
global _start
extern stage2_main

_start:
    cli
    call stage2_main
    hlt
