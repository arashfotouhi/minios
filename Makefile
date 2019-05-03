C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = gcc
CCFLAGS = -march=i386
LD = ld
AS = nasm
EMU = qemu-system-i386
#EMUFLAGS = -m 1024 -boot c -enable-kvm -smp 3
EMUFLAGS = -device isa-debug-exit,iobase=0xf4,iosize=0x04 -fda

all: minios

minios: boot/boot.bin kernel.bin
	cat $^ > minios

kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	$(CC) -ffreestanding -c $< -o $@

%.o: %.asm
	$(AS) $< -f elf64 -o $@
	
%.bin: %.asm
	$(AS) $< -f bin -I '../../16bit/' -o $@

clean:
	rm -rf *.bin *.dis *.map *.o minios	
	rm -rf kernel/*.o boot/*.bin drivers/*.o

kernel.dis: kernel.bin
	ndisasm -b 64 $< > $@

run: all
	$(EMU) $(EMUFLAGS) minios
