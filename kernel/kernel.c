#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../lib/libc/string.h"

void main (void) 
{
	clear_screen();
	print("MiniOS kernel successfully loaded.\n");
	print("Welcome!\n");

	isr_install();
	irq_install();
}

void user_input (char *input)
{
	if(strcmp(input, "END") == 0) {
		print("Stopping the CPU!\n");
		asm volatile("hlt");
	}
	print("You said: ");
	print(input);
	print("\n> ");
}
