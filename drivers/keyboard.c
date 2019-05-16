#include "keyboard.h"
#include "../kernel/low_level.h"
#include "../kernel/kernel.h"
#include "../cpu/isr.h"
#include "screen.h"

#define SC_MAX 58
#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

static const char keyboard_key[0x40] = {
#include "keymap.h"
};

static void keyboard_callback (registers_t regs)
{
	u8 scancode = port_byte_in(0x60);
	
	if(scancode > SC_MAX)
		return;
	if(scancode == BACKSPACE) {
		backspace(key_buffer);
		print_backspace();
	} else if(scancode == ENTER) {
		print("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
	} else {
		char letter = keyboard_key[(int)scancode];
		char str[2] = {letter, '\0'};
		append(key_buffer, letter);
		print(str);
	}
}

void init_keyboard (void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
