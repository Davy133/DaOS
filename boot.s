[org 0x7c00]


[bits 16]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp
mov bx, MSG_REAL_MODE
call print_string
call load_kernel
call pm_switch
jmp $

%include "src/print_string.s"
%include "disk/disk_load.s"
%include "pm/gdt.s"
%include "pm/print_string_pm.s"
%include "pm/pm_switch.s"

[bits 16]

load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
ENTRY_POINT:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE:
    db 0
MSG_LOAD_KERNEL:
    db "Loading kernel into memory.",0
MSG_PROT_MODE:
    db "Successfully landed in 32-bit Protected Mode.",0
MSG_REAL_MODE: 
    db "Started in 16-bit Real Mode.",0


times 510-($-$$) db 0 
dw 0xaa55