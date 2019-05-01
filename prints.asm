prints:
	pusha
	mov ah, 0x0e
loop:
	mov al, [bx]
	int 0x10
	add bx, 0x1
	mov cx, [bx]
	cmp cx, 0
	jne loop

	popa
	ret
