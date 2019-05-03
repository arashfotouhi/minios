#include "../drivers/screen.h"

void main () {
	//char* Video_memory = (char*) 0xb8000;
	//*Video_memory = 'X';
	//clear_screen();
	print_char('A', 0, 0, WHITE_ON_BLACK);
	//print_char('d', -1, -1, WHITE_ON_BLACK);
	//print_char('e', -1, -1, WHITE_ON_BLACK);
}
