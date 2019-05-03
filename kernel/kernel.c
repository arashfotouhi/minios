#include "../drivers/screen.h"

void main () {
	clear_screen();
	print_char('A', 0, 0, WHITE_ON_BLACK);
	print_char('d', 1, 2, WHITE_ON_BLACK);
}
