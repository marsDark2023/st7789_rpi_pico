#include "spi.h"
#include "pico/time.h"

#define io_pinit()      spi_init_pins()
#define io_wbyt(dat)    spi_wrtie_byte(dat)
#define io_wwd(dat)     spi_write_word(dat) 
#define io_wcmd(cmd)    spi_write_command(cmd)

#define IO_RESET io_pinit();       \
                gpio_put( RST, 0); \
                sleep_ms( 100);     \
                gpio_put( RST, 1);  \
                sleep_ms( 100);     
