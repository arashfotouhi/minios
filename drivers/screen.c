#include "screen.h"
#include "../kernel/low_level.h"
#include "../kernel/util.h"

int get_screen_offset (int col, int row) { 
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
	//TODO: needs to be properly implemented
	return offset;
}

int print_char (char character, int col, int row, char attribute_byte)
{
	char *vidmem = (char *)VIDEO_ADDRESS;

	/****************** DEBUG BLOCK *******************/

    // This produces a music note symbol instead of 'A'
    // the music symbol is probably represented by ascii 0x0E
    vidmem[0] = 0x41; //'A'
    vidmem[1] = 0x0E; //yellow on black

    // This also produces the undesired result above as expected
    // because this is equivalent to the above block of code
    //*vidmem = 0x41;
    //*(vidmem+1) = 0x0E;

    // This produces a yellow 'A' on black background as expected.
    //*vidmem = 0x41;
    //vidmem++;
    //*vidmem = 0x0E;

    // This also produces the correct result (ie, 'A', yellow on black)
    //*vidmem = 0x41; 
    //vidmem = vidmem + 1;
    //*vidmem = 0x0E;

	return 0;
	/**************** END DEBUG BLOCK **********************/

	if (!attribute_byte) {
		attribute_byte = WHITE_ON_BLACK;
	}

	int offset;
	if (col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor();
	}

	if (character == '\n') {
		int rows = offset / (2 * MAX_COLS);
		offset = get_screen_offset(79, rows);
	} else {
		vidmem[offset] = (attribute_byte << 8) + character;
		//temp ++;
		//*temp = attribute_byte;
		offset += 2;
	}

	if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++)
            memory_copy(get_screen_offset(0, i) + VIDEO_ADDRESS,
                        get_screen_offset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_screen_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
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

void print_at (char* message, int col, int row)
{
	int offset;

	if (col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
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

void print(char* message)
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
