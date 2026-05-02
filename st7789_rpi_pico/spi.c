/* soft spi, rpi pico gpio */
#include "include/spi.h"
int spi_init_pins(){
    gpio_init( CS );
    gpio_init( DC );
    gpio_init( CLK );
    gpio_init( MOSI );
    gpio_init( RST );

    gpio_set_dir ( CS,  GPIO_OUT );
    gpio_set_dir ( DC,  GPIO_OUT );
    gpio_set_dir ( CLK, GPIO_OUT );
    gpio_set_dir ( MOSI,GPIO_OUT );
    gpio_set_dir ( RST, GPIO_OUT );

    gpio_put( CLK, 1); /* mode 3 */
    
    return 0;
}

int spi_io_write_byte( u8 byte ){

    for( int i = 0; i<8; ++i){
        u8 bit = byte >> 7;
        byte <<= 1;

        gpio_put( CLK, 0);
        gpio_put( MOSI, bit);
        gpio_put( CLK, 1);
    }
    return 0;
}

int spi_wrtie_byte( u8 dat ){
    gpio_put( CS, 0); /* chip select */
    gpio_put( DC, 1);

    spi_io_write_byte( dat );

    gpio_put( CS, 1);
    return 0;
}
int spi_write_word( u16 dat ){
    gpio_put( CS, 0); /* chip select */
    gpio_put( DC, 1);

    spi_io_write_byte( (dat>>8) );
    spi_io_write_byte( (dat & 0xff) );

    gpio_put( CS, 1);
    return 0;
}
int spi_write_command( u8 cmd ){
    gpio_put( CS, 0); /* chip select */
    gpio_put( DC, 0);

    spi_io_write_byte( cmd );

    gpio_put( CS, 1);
    return 0;
}