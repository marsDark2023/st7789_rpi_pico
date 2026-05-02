#pragma once
#include "hardware/gpio.h"
#include "mytype.h"

/* PINS */
#define CS      1
#define DC      6
#define CLK     2
#define MOSI    3
#define RST     5

int spi_init_pins();

int spi_wrtie_byte( u8 dat );
int spi_write_word( u16 dat );
int spi_write_command( u8 cmd );
