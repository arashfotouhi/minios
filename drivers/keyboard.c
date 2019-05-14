#include "keyboard.h"
#include "../kernel/low_level.h"
#include "../cpu/isr.h"
#include "screen.h"

static char const* keyboard_key[0x40] = {
#include "keymap.h"
};

void print_key (u8 scancode)
{
	print(keyboard_key[scancode]);	
}

static void keyboard_callback (registers_t regs)
{
	// you have to actually read from 0x60
	// otherwise the interrupt will only fire
	// once and won't fire again for subsequent
	// key presses.
	u8 scancode = port_byte_in(0x60);

	//print_uint(scancode);
	print_key(scancode);
}

void init_keyboard (void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
