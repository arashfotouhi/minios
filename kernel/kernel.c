#include "../drivers/screen.h"
#include "../cpu/isr.h"

void main (void) 
{
	clear_screen();
	print("MiniOS kernel successfully loaded.\n");
	print("Welcome!\n");

	isr_install();
	irq_install();
}
