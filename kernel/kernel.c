#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main (void) 
{
	clear_screen();
	print("MiniOS kernel successfully loaded.\n");
	print("Welcome!\n");

	isr_install();
	
	// Testing interrupts
	__asm__ __volatile__("int $0");
	__asm__ __volatile__("int $1");
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
	__asm__ __volatile__("int $4");
	__asm__ __volatile__("int $5");
	__asm__ __volatile__("int $6");
	__asm__ __volatile__("int $7");
	//__asm__ __volatile__("int $8"); // tried this in emalator and unexpected stuff happens, don't know why.
	// Tried the remainder of this block
	// and same unexpected stuff as before
	// happens, so some of this interrupts
	// below generate loops (maybe kernel
	// panic?), maybe this is an expected
	// behavior, but I have to investigate
	/*__asm__ __volatile__("int $9");
	__asm__ __volatile__("int $10");
	__asm__ __volatile__("int $11");
	__asm__ __volatile__("int $12");
	__asm__ __volatile__("int $13");
	__asm__ __volatile__("int $14");
	__asm__ __volatile__("int $15");
	__asm__ __volatile__("int $16");
	__asm__ __volatile__("int $17");
	__asm__ __volatile__("int $18");
	__asm__ __volatile__("int $19");
	__asm__ __volatile__("int $20");
	__asm__ __volatile__("int $21");
	__asm__ __volatile__("int $22");
	__asm__ __volatile__("int $23");
	__asm__ __volatile__("int $24");
	__asm__ __volatile__("int $25");
	__asm__ __volatile__("int $26");
	__asm__ __volatile__("int $27");
	__asm__ __volatile__("int $28");
	__asm__ __volatile__("int $29");
	__asm__ __volatile__("int $30");
	__asm__ __volatile__("int $31");*/

	asm volatile("sti");
	//init_timer(50);

	init_keyboard();
}
