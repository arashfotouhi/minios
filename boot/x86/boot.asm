; The line below provides a location reference for the
; rest of the program. The BIOS loads this image starting
; at 0x7c00. If we don't provide the line below, we have 
; to manually offset all our addresses by 0x7c00. This is
; tedious so we add this to make things easier. So for
; example every time we access the 0x0 memory location
; from now on, it will actually be 0x7c00 as the BIOS
; sees it.
[org 0x7c00]

; Here we're setting the data segment to 0x0
; (or effectively 0x7c00 as the BIOS sees it).
; The data segment contains all the constants
; and data in our program. If we ommit this block
; the code will still work in QEMU but won't
; work in actual hardware. I'm still not quite
; sure why but I think QEMU automatically
; resets the data segment for us whereas
; in actual hardware (or at least the old
; laptop that I was using) this has to be set
; manually.
mov ax, 0x0000
mov ds, ax

; This is the location where we are going to be
; loading our kernel to. Just defining a constant
; here so we can use it later.
KERNEL_OFFSET equ 0x1000

; BOOT_DRIVE is a global variable that we have
; defined (see towards the bottom of this file
; where global variables are defined). dl is
; where BIOS stores our boot drive. The boot
; drive is just a number that BIOS assigns to
; the drive that we are booting from (USB, DVD, etc)
; We don't really care how this number is assigned
; or what it inherently means. All we care about
; is that BIOS identifies our boot drive with
; this number and later we need this number to
; refer to out boot device.
mov [BOOT_DRIVE], dl

; Here we are setting up the stack. bp is the stack
; base pointer (bottom of stack). This value does
; not change automatically and unless we change it
; manually it's fixed for the rest of the program.
; sp is the stack pointer and it points to the top
; of the stack. This pointer does change implicitly.
; For example when we use push and pop functions, this
; pointer gets incremented or decremeneted accordingly.
; The stack grows "backwards" (ie towards 0x0). So the
; stack pointer is decremented every time we push items
; on the stack, therefore we must initialize our stack far
; away from the location of our program to ensure we
; don't overwrite our code. Here we are setting the base
; at 0x9000 (ie far away from where out kernel is going
; to be (ie 0x1000). And since the stack is empty initially,
; we set sp equal to bp.
mov bp, 0x9000
mov sp, bp

; Our printstr routine takes bx as the argument. Here
; we are just passing a constant string (ie our message)
; to the printstr routine. The message states that
; we are in "real mode". We haven't yet transitioned
; into "protected mode" and we are still in 16 bit mode.
mov bx, MSG_REAL_MODE
call printstr

; Calling the routine that loads the kernel onto disk.
; Note that this does NOT execute the kernel yet, it
; just loads the kernel on the disk. We will start
; executing the kernel after switching to 32 bit mode
call load_kernel

; Calling the routine that switches to 32 bit mode.
; After calling this routine we will be operating
; in 32 bit mode
call switch_to_pm

; All the include assembly include files
; that we are using in this source file
%include "boot/x86/print/printstr.asm" ; used for printing strings on the screen in 16 bit mode
%include "boot/x86/disk/disk_load.asm" ; used for loading blocks onto the disk
%include "boot/x86/pm/gdt.asm" ; used for defining the Global Decriptor Table
%include "boot/x86/pm/printstrpm.asm" ; used for printing strings in 32 bit mode
%include "boot/x86/pm/switch_to_pm.asm" ; used for switching to 32 bit mode

; At this point we have to make sure we are telling assembler that we
; are operating in 16 bit mode
[bits 16]

; The operating system is not going to fit in the first sector of the
; boot device (that's only 512 bytes). So we need to load the operating
; system from the boot device onto the memory for the cpu to execute. Here
; we're loading 50 sectors from the boot disc onto memory location defined
; by KERNEL_OFFSET. Later we will explicitly call and give control of
; exeuction to this location.
load_kernel:
	; print the appropriate message on the screen
	mov bx, MSG_LOAD_KERNEL
	call printstr

	mov bx, KERNEL_OFFSET
	mov dh, 50 
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

; We will be operating in 32 bit protected mode at this point so we
; need to explicitly let assembler know
[bits 32]

; The switch_to_pm routine jumps here
BEGIN_PM:
	; Display message that we're in protected mode
	mov ebx, MSG_PROT_MODE
	call printstrpm

	; Call the kernel which we know for sure is located at KERNEL_OFFSET
	; because we loaded it from disk at this location.
	call KERNEL_OFFSET

        ;Warn if the kernel stopped
        mov ebx, "Kernel Stop. Please try again."

	; We should never reach this place so just loop indefinitely
	jmp $

; Global variables
BOOT_DRIVE: db 0 ; Holds our boot drive ID / number

; Message strings
MSG_REAL_MODE db "Started in 16-bit Real Mode",0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode",0
MSG_LOAD_KERNEL db "Loading kernel into memory",0

; BIOS looks for the magic number 0xAA55 at the end of the
; first sector and that's how it knows this device is bootable
; so here were are zeroing all the remaining bytes until the 
; last byte which we initialize with 0xAA55
times 510-($-$$) db 0
dw 0xaa55
