CC = gcc
LD = ld
AS = nasm
ASFLAGS = -f
EMU = qemu-system-x86_64
EMUFLAGS = -m 1024 -boot c -enable-kvm -smp 3

minios: boot.bin kernel.bin
	cat boot.bin kernel.bin > minios

boot.bin: boot.asm print/printstr.asm pm/printstrpm.asm print/printhex.asm disk/disk_load.asm pm/gdt.asm pm/switch_to_pm.asm 
	$(AS) boot.asm $(ASFLAGS) bin -o boot.bin

kernel.bin: kernel.o
	$(LD) -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

kernel.o: kernel.c
	$(CC) -ffreestanding -c kernel.c -o kernel.o

run:
	$(EMU) $(EMUFLAGS) minios

clean:
	rm -rf *.bin *.o minios	
