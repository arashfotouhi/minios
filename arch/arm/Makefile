CROSS_COMPILE ?= arm-linux-gnueabihf-

all: arch/arm/boot.s
	$(CROSS_COMPILE)as arch/arm/boot.s -o arch/arm/boot.o
	$(CROSS_COMPILE)objcopy arch/arm/boot.o arch/arm/boot.bin -O binary
	$(CROSS_COMPILE)objdump -D -b binary -marm arch/arm/boot.bin > arch/arm/boot.lst

clean:
	rm *.o *.bin *.lst
