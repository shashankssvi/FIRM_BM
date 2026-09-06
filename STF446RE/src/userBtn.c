#include<stdint.h>
#include "f446re.h"

// void delay(uint32_t);

void userBtn(void){
    AHB1EB|=(1<<2)|1;
    GPIOA_MODER|=(0b01<<10);
    GPIOC_MODER|=(0b00<<26);

    while (1)
    {
        if (!(GPIOC_IDR&(1<<13)))
            GPIOA_BSRR|=(1<<21);
        else
            GPIOA_BSRR|=(1<<5);
        // delay(10);
    }
    
}

// void delay(uint32_t a){
//     for(uint16_t b = 5000;b>0;--b)
//         for(volatile uint32_t i=0;i<a;i++);
// }