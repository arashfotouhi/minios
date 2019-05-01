[org 0x7c00]

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 2
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call printhex

mov dx, [0x9000 + 512]
call printhex

mov bx, BOOTLOADER_STRING
mov dx, 0x1fb6
call printstr
call printhex

jmp $

%include "printstr.asm"
%include "printhex.asm"
%include "disk_load.asm"

BOOTLOADER_STRING:
	db 'minios_bootloader',0

BOOT_DRIVE: db 0

times 510-($-$$) db 0

dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
