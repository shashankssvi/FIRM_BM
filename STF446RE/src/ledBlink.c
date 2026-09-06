#include<stdint.h>
#include "f446re.h"

void delay(uint32_t);

void blinkLED(void){
    AHB1EB|=1;
    GPIOA_MODER|=(0b01<<10);
    GPIOA_ODR|=(1<<5);

    // while (1)
    // {
        //delay(100);
        if(!(GPIOA_ODR&(1<<5))){
            GPIOA_BSRR|=(1<<5);blinkLED();
        }
        else{
            GPIOA_BSRR|=(1<<21);
        }
        
    // }/
}

void delay(uint32_t a){
    for(uint16_t b = 5000;b>0;--b)
        for(volatile uint32_t i=0;i<a;i++);
}