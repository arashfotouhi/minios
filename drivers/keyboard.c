#include "keyboard.h"
#include "../kernel/low_level.h"
#include "../cpu/isr.h"
#include "screen.h"

static void keyboard_callback (registers_t regs)
{
	print("Keyboard key pressed.\n");
}

void init_keyboard (void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
