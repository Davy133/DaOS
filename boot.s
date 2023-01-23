[org 0x7c00]
mov bp, 0x9000
mov sp, bp
call pm_switch
jmp $

%include "gdt.s"
%include "pm_switch.s"

[bits 32]
ENTRY_POINT:
    mov al, "A"
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $


times 510-($-$$) db 0 
dw 0xaa55