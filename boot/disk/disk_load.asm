disk_load:
	push dx ; First push all the register onto the stack to recover later
	mov ah, 0x02 ; Set operation to read sectors from drive
	mov al, dh ; Number of sectors to read (this was passed as an arg before calling this routine)
	mov ch, 0x00 ; Cylinder 0
	mov dh, 0x00 ; Head 0
	mov cl, 0x02 ; Sector 2
	int 0x13 ; Raise BIOS interrupt 13 (Low level disk services interrupt)

	jc disk_error ; If there's a carry, there was an error in disk read so jumo to disk_error

	pop dx ; Recover all the registers to initial state
	cmp dh, al ; Check to make sure actual sectors read is equal to requested sector count
	jne disk_error ; If the above is not equal jumo to disk_error
	ret

; Print disk error message and do an infinite loop
disk_error:
	mov bx, DISK_ERROR_MSG
	call printstr
	jmp $

DISK_ERROR_MSG db "Disk read error!",0 ; Global string used to hold disk error message
