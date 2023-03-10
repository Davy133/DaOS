#include "screen.h"
#include "types.h"

size_t strlen(const char *buffer){
    size_t i;
    for(i=0;buffer[i]!='\0';i++);
    return i;
}

enum vga_color{
    VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

size_t terminal_row;
size_t terminal_column;
uint8 terminal_color;
uint16* terminal_buffer;

static inline uint8 vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16 vga_entry(unsigned char uc,uint8 color)
{
    return (uint16) uc | (uint16) color << 8;
}

static inline void jump_nextline(){
    terminal_row++;
    terminal_column = 0;
}

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY,VGA_COLOR_BLACK);
    terminal_buffer = (uint16*)VIDEO_ADDRESS;
    for(size_t y = 0;y<VGA_HEIGHT;y++){
        for(size_t x = 0; x<VGA_WIDTH;x++){
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8 color){
    terminal_color = color;
}

void terminal_putentryat(char c, uint8 color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++){
        if(data[i] == '\n'){
            terminal_putchar('\0');
            jump_nextline();
        }else{
            terminal_putchar(data[i]);
        }
    }
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

extern void main(){
    terminal_initialize();
    terminal_writestring("Hello World!\n");
}