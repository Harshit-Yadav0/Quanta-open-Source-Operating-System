; context_switch.asm
; Save old ESP, load new ESP

global context_switch_asm

context_switch_asm:
    ; stack:
    ; [esp + 4] = &old_esp
    ; [esp + 8] = &new_esp

    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]    ; eax = &old_esp
    mov [eax], esp       ; save current ESP

    mov eax, [ebp + 12]  ; eax = &new_esp
    mov esp, [eax]       ; load new ESP

    pop ebp
    ret
