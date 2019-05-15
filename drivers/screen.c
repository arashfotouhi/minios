#include "screen.h"
#include "../kernel/low_level.h"
#include "../lib/libc/mem.h"

int get_screen_offset (int col, int row) 
{ 
	return 2 * (row * MAX_COLS + col);
}

void set_cursor (int offset)
{
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor ()
{
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset * 2;
}

int handle_scrolling (int offset)
{
	if (offset < (2 * MAX_COLS * MAX_ROWS)) {
		return offset;
	}

	int i;
	for (i=1; i < MAX_ROWS; i++) {
		memory_copy((u8 *)(get_screen_offset(0, i) + VIDEO_ADDRESS),
				(u8 *)(get_screen_offset(0, i-1) + VIDEO_ADDRESS),
				MAX_COLS * 2);
	}
	
	char* last_line = (char *)(get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS);
	for (i=0; i < MAX_COLS * 2; i++) {
		last_line[i] = 0;
	}

	offset -= 2 * MAX_COLS;

	return offset;
}

int print_char (char character, int col, int row, char attribute_byte)
{
	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
	if (!attribute_byte) 
		attribute_byte = WHITE_ON_BLACK;

	int offset;
	if (col >= 0 && row >= 0)
		offset = get_screen_offset(col, row);
	else
		offset = get_cursor();

	if (character == '\n') {
		int rows = offset / (2 * MAX_COLS);
		offset = get_screen_offset(MAX_COLS, rows);
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] = attribute_byte;
		offset += 2;
	}

	offset = handle_scrolling(offset);
	set_cursor(offset);
	return offset;
}

int get_offset_row (int offset)
{
	return offset / (2 * MAX_COLS);
}

int get_offset_col (int offset)
{
	return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

void print_at (const char* message, int col, int row)
{
	int offset;

	if (col >= 0 && row >= 0)
		offset = get_screen_offset(col, row);
	else {
		offset = get_cursor();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
	
	int i = 0;
	while (message[i] != 0) {
		offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void print(const char* message)
{
	print_at(message, -1, -1);
}

void clear_screen ()
{
	int screen_size = MAX_COLS * MAX_ROWS;
	int i;
	unsigned char* screen = (unsigned char*) VIDEO_ADDRESS;

	for (i=0; i < screen_size; i++) {
		screen[i*2] = ' ';
		screen[i*2 + 1] = WHITE_ON_BLACK;
	}
	set_cursor(get_screen_offset(0, 0));
}

void print_uint (unsigned int n)
{
	unsigned char zero = 48;
	int reversed = 0;
	int digit_count = 0;
	if (!n) { 
		print_char(zero, -1, -1, WHITE_ON_BLACK);
		return;
	}
	while (n > 0) {
		reversed += n % 10;
		reversed *= 10;
		n /= 10;
		digit_count++;
	}
	reversed /= 10;
	while (digit_count-- > 0) {
		print_char(reversed % 10 + zero, -1, -1, WHITE_ON_BLACK);
		reversed /= 10;
	}
}

void test_screen (void) 
{
	int row;
	int col;
	char ch = 0;
	char forground = 8;
	char background = 0;
	char attribute;

	for (col = 0; col < MAX_COLS; col++) {
		for (row = 0; row < MAX_ROWS; row++) {
			attribute = (background++ << 8) + forground++;		
			print_char(ch++, col, row, attribute);
		}
	}
}

void print_backspace (void)
{
	int offset = get_cursor() - 2;
	int row = get_offset_row(offset);
	int col = get_offset_col(offset);
	print_char(0x08, col, row, WHITE_ON_BLACK);
}
