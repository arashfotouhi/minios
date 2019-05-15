#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int print_char (char character, int col, int row, char attribute_byte);
void print_at (const char* message, int col, int row);
void print (const char* message);
void print_uint (unsigned int n);
void clear_screen (void);
void print_backspace (void);
