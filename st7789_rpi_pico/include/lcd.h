#pragma once

void
lcdInit(void);
void
addrSet(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );
void
lcd_clear(void);

void newLine(void);
void print( char * string);
void print_u32_x( unsigned int n );
void
serial_print_dma();
