void main () {
	char* Video_memory = (char*) 0xb8000;
	*Video_memory = 'X';
}
