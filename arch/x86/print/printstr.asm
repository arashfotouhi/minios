; Simple routine for printing a string on the display
printstr:
	pusha ; First push everything on the stack for later recovery

	; We'll be using interrupt 0x10 to print to screen. The interrupt 
	; "parameter" comes through the AX register. 0xE is the value that
	; says write character in TTY mode. See BIOS interrupt table for
	; details.
	mov ah, 0x0e
loop_printstr:
	; We use bx for passing arguments to this routine. Here since the
	; argument that is bassed is the address of the start of the
	; string, we use [] to get the content of the address. The lower
	; bits of the AX register hold the character to be displayed.
	mov al, [bx]
	; Call the interrupt to actually write the character to display.
	int 0x10
	add bx, 0x1 ; Go to the next character
	mov cx, [bx] ; Place character in CX for checking end of character
	cmp cl, 0 ; Is this the end of character?
	jne loop_printstr ; If not end of character print next character

	popa ; Restore everything on the push stack
	ret
