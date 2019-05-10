#include "../drivers/screen.h"
#include "../cpu/isr.h"

void main (void) 
{
	clear_screen();
	print("MiniOS kernel successfully loaded.\n");
	print("Welcome!\n");

	isr_install();
	
	// Testing interrupts
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}
