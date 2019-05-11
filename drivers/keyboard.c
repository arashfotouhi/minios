#include "keyboard.h"
#include "../kernel/low_level.h"
#include "../cpu/isr.h"
#include "screen.h"

static void keyboard_callback (registers_t regs)
{
	// you have to actually read from 0x60
	// otherwise the interrupt will only fire
	// once and won't fire again for subsequent
	// key presses.
	u8 scancode = port_byte_in(0x60);

	print_uint(scancode);
	print("\n");
}

void init_keyboard (void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
