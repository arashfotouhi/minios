#include "../drivers/screen.h"

void main (void) 
{
	clear_screen();
	int i;
	for (i=0; i<1000; i++) {
		//print("MiniOS kernel successfully loaded.\n");
		//print("Welcome!");
		print_int(i);
		print(" ");
	}
}
