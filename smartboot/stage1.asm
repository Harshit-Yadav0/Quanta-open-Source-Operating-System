[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, msg
.print:
    lodsb
    or al, al
    jz load_stage2
    mov ah, 0x0E
    int 0x10
    jmp .print

load_stage2:
    mov bx, 0x8000        ; stage2 load address
    mov ah, 0x02
    mov al, 10            ; sectors
    mov ch, 0
    mov dh, 0
    mov cl, 2
    int 0x13
    jc $

    jmp 0x0000:0x8000

msg db "SmartBoot Stage1",0

times 510-($-$$) db 0
dw 0xAA55
