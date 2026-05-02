//LCDst7789 
#include "include/io.h"
#include "include/lcd.h"
#include "include/font.h"
#include "pico/stdlib.h"
/* lcd info */
#define LCDx 240
#define LCDy 320
/* cursor */
#define CURSORCOLOR 0x1f

/* st7789 hardware */
void
lcd_addrSet(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );
void
lcdInit(void){
    IO_RESET;
    io_wcmd(0x11);
    sleep_ms(100);

    io_wcmd(0x36);
    sleep_ms(100);
    io_wbyt(0x00);

    io_wcmd(0x3a);
    io_wbyt(0x05);

    io_wcmd(0xb2);
    io_wbyt(0x0c);
    io_wbyt(0x0c);
    io_wbyt(0x00);
    io_wbyt(0x33);
    io_wbyt(0x33);

    io_wcmd(0xb7);
    io_wbyt(0x35);

    io_wcmd(0xbb);
    io_wbyt(0x19);

    io_wcmd(0xc0);
    io_wbyt(0x2c);

    io_wcmd(0xc2);
    io_wbyt(0x01);

    io_wcmd(0xc3);
    io_wbyt(0x12);

    io_wcmd(0xc4);
    io_wbyt(0x20);

    io_wcmd(0xc6);
    io_wbyt(0x0f);

    io_wcmd(0xd0);
    io_wbyt(0xa4);
    io_wbyt(0xa1);

    io_wcmd(0xe0);
    unsigned char data[] ={0xd0,0x04,0x0d,0x11,0x13,0x2b,0x3f,0x54,0x4c,0x18,0x0d,0x0b,0x1f,0x23};
    for(int i = 0 ; i<14; ++i){
        io_wbyt(data[i]);
    }

    io_wcmd(0xe1);
    unsigned char data2[] = {0xd0,0x04,0x0c,0x11,0x13,0x2c,0x3f,0x44,0x51,0x2f,0x1f,0x1f,0x20,0x23};
    for(int i =0 ; i<14 ; ++i){
        io_wbyt(data2[i]);
    }

    io_wcmd(0x21);

    io_wcmd(0x29);
}
void
lcd_addrSet(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 ){
    io_wcmd(0x2a);
    io_wwd(x1);
    io_wwd(x2);
    io_wcmd(0x2b);
    io_wwd(y1);
    io_wwd(y2);
    io_wcmd(0x2c);
}
void
lcd_clear(void){
    addrSet(0,0,239,319);
    for(int i = 0 ; i < 320; ++i){
        for(int j = 0 ; j < 240; ++j){
            io_wwd( 0 );
        }
    }
}


/* cursor */
void
Cursor_clear(void);

struct Cursor {
    unsigned int x ;
    unsigned int  y;
};
#define cursor_max_x 29
#define cursor_max_y 24
struct Cursor cursor = {0};
void Cursor_incream(void){
    ++(cursor.x);
    if(cursor.x > cursor_max_x){
        cursor.x = 0;
        ++(cursor.y);
        if(cursor.y > cursor_max_y){
            cursor.y = 0;
            lcd_clear();
        }
    }
}
void Cursor_newLine(void){
    Cursor_clear();
    cursor.x = 0;
    ++(cursor.y);
    if(cursor.y > cursor_max_y){
        lcd_clear();
        cursor.y = 0;
    }
}
void
Cursor_show(void){
    unsigned int x1 = cursor.x * FONTWIDTH;
    unsigned int y1 = cursor.y * FONTSIZE;
    unsigned int x2 = x1 + FONTWIDTH;
    unsigned int y2 = y1 + FONTSIZE;
    addrSet(x1,y1,x2-1,y2-1);
    for(int i = 0 ; i<FONTSIZE; ++i){
        for( int j = 0; j<8; ++j){
            io_wwd(CURSORCOLOR);
        }
    }
}
void
Cursor_clear(void){
    unsigned int x1 = cursor.x * FONTWIDTH;
    unsigned int y1 = cursor.y * FONTSIZE;
    unsigned int x2 = x1 + FONTWIDTH;
    unsigned int y2 = y1 + FONTSIZE;
    addrSet(x1,y1,x2-1,y2-1);
    for(int i = 0 ; i<FONTSIZE; ++i){
        for( int j = 0; j<8; ++j){
            io_wwd( 0 );
        }
    }
}


/* interfce */
void
__putchar(unsigned int x, unsigned int y, char c){
    u8 * data = font_get(c);
    if(!data){
        return;  // no such letter in list
    }
    addrSet(x, y, x +7 , y +FONTSIZE-1);
    for(int i = 0 ; i<FONTSIZE; ++i){
        unsigned char line = data[i];
        for( int j = 0; j<8; ++j){
            u8 bit = line >> 7;
            line <<= 1;
            unsigned int color = bit==WHITE ? RGBWHITE : RGBBLACK;
            io_wwd( color );
        }
    }
}
void
putchar( char c){
    if(c == '\n'){
        Cursor_newLine();
        Cursor_show();
        return;
    }
    __putchar((FONTWIDTH * cursor.x), (FONTSIZE * cursor.y), c);
    Cursor_incream();
    Cursor_show();
}
void newLine(void){
    Cursor_newLine();
    Cursor_show();
}
void print( char * string){
    for(unsigned int i = 0; string[i] != 0; i++){
        if(string[i] == '\n'){
            Cursor_newLine();
            continue;
        }
        __putchar((FONTWIDTH * cursor.x), (FONTSIZE * cursor.y), string[i]);
        Cursor_incream();
    }
    Cursor_show();
}
void print_u32_x( unsigned int n ){
    static char print_u32_x_table[16] = "0123456789abcdef";
    for( int i = 0 ; i < 8; ++ i){
        unsigned int msb = n >> 28;
        n <<= 4;
        putchar( print_u32_x_table[ msb ] );
    }
}


