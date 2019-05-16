#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../lib/libc/string.h"
#include "../lib/libc/mem.h"

void kernel_main (void) 
{
	clear_screen();
	kprint("MiniOS kernel successfully loaded.\n");
	kprint("Welcome!\n");

	isr_install();
	irq_install();
}

void user_input (char *input)
{
	if(strcmp(input, "end") == 0) {
		kprint("Stopping the CPU!\n");
		asm volatile("hlt");
	} else if(strcmp(input, "page") == 0) {
		u32 phys_addr;
		u32 page = kmalloc(1000, 1, &phys_addr);
		char page_str[16] = "";
		hex_to_ascii(page, page_str);
		char phys_str[16] = "";
		hex_to_ascii(phys_addr, phys_str);
		kprint("Page: ");
		kprint(page_str);
		kprint(", physical address: ");
		kprint(phys_str);
		kprint("\n");
	}
	kprint("You said: ");
	kprint(input);
	kprint("\n> ");
}
