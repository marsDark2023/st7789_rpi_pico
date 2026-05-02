
#include "include/header.h"
#include "hardware/structs/systick.h"
#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/exception.h"

#include "include/lcd.h"

#include "pico/multicore.h"

/* defines */
#include <stdint.h>
unsigned int __lr = 0;
volatile unsigned int __systick_tick = 0; 
void SysTick_Init(void);
void isr_systick(void);


__keep void wait_for_ms( unsigned int ms ){
    __systick_tick = 0;
    while( __systick_tick < ms ){
    } ;
    print( " lr: ");
    print_u32_x( __lr );
    print( "\n" );
}

void core1_entry(){
        
    gpio_init( 25 );
    gpio_set_dir( 25, GPIO_OUT);
    while(1){
        gpio_put( 25, 1);
        sleep_ms( 3000);
        gpio_put( 25, 0);
        sleep_ms( 3000);
        
    }
}


int main()
{
    uint32_t tick_now ;

    stdio_init_all();

    lcdInit();
    multicore_launch_core1(core1_entry);
    SysTick_Init();

    while(1){
        
        wait_for_ms(1000);
        
      
    }
    
}

/*
exception_handler_t  void * (void)
*/


void isr_systick(void){
    ++ __systick_tick;
}
#define SYSTICK_IRQ 15
void SysTick_Init(void){
   systick_hw->csr = 0 ;
    systick_hw->rvr = 140000;
    systick_hw->cvr = 0 ;
    systick_hw->csr =  M0PLUS_SYST_CSR_CLKSOURCE_BITS |
        M0PLUS_SYST_CSR_TICKINT_BITS |
        M0PLUS_SYST_CSR_ENABLE_BITS ;
}

