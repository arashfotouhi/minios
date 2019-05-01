printstr:
	pusha
	mov ah, 0x0e
loop_printstr:
	mov al, [bx]
	int 0x10
	add bx, 0x1
	mov cx, [bx]
	cmp cl, 0
	jne loop_printstr

	popa
	ret
