AS = nasm
ASFLAGS = -f
EMU = qemu-system-x86_64
EMUFLAGS = -m 1024 -boot c -enable-kvm -smp 3

boot.bin: boot.asm printstr.asm printhex.asm disk_load.asm
	$(AS) boot.asm $(ASFLAGS) bin -o boot.bin

run:
	$(EMU) $(EMUFLAGS) boot.bin

clean:
	rm -f boot.bin
