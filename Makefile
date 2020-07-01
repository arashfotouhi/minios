C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c lib/libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h lib/libc/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = gcc

# The -fno-pie is used here in order to make sure the compiler does
# not generate position independant executables. On Fedora my compiler
# did not generate position independent executables and things worked
# fine without this flag, but switching to Arch Linux, things broke.
# Now adding this flag to explicitly state that position independent
# executable should be stopped.

CCFLAGS = -m32 -g -Wall -fno-pie -fno-stack-protector
LD = ld
AS = nasm
EMU = qemu-system-i386
#EMUFLAGS = -m 1024 -boot c -enable-kvm -smp 3
EMUFLAGS = -device isa-debug-exit,iobase=0xf4,iosize=0x04 -fda

all: minios

minios: boot/x86/boot.bin kernel.bin
	cat $^ > minios

kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	$(CC) $(CCFLAGS) -ffreestanding -c $< -o $@

%.o: %.asm
	$(AS) $< -f elf32 -o $@
	
%.bin: %.asm
	$(AS) $< -f bin -I '../../16bit/' -o $@

clean:
	rm -rf *.bin *.dis *.map *.o minios	
	rm -rf kernel/*.o boot/x86/*.bin drivers/*.o cpu/*.o lib/libc/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

run: all
	$(EMU) $(EMUFLAGS) minios
