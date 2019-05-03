[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

printstrpm:
	pusha
	mov edx, VIDEO_MEMORY

loop_printstrpm:
	mov al, [ebx]
	mov ah, WHITE_ON_BLACK
	
	cmp al, 0
	je printstrpm_done

	mov [edx], ax

	add ebx, 1
	add edx, 2

	jmp loop_printstrpm

printstrpm_done:
	popa
	ret
