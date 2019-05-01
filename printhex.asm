printhex:
	pusha
	mov bx, HEX_OUT
	add bx, 2	;need to move to after "0x0"
	mov ax, 0
loop_printhex:
	rol dx, 0x4
	mov cx, dx
	and cx, 0xF
	cmp cx, 0xA
	jge alpha_digit
	add cx, 0x30
	jmp update_out
alpha_digit:
	sub cx, 0xA
	add cx, 0x41
	jmp update_out
update_out:
	mov [bx], cx
	add ax, 0x1
	cmp ax, 0x4
	je parsed
	add bx, 0x1
	jmp loop_printhex
parsed:
	mov bx, HEX_OUT
	call printstr

	popa
	ret

HEX_OUT: db '0x0000',0
