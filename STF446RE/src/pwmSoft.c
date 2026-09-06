// The "Soft" PWM (Pulse Width Modulation)

#include<stdint.h>
#include "f446re.h"


int pwmSodt(void){
    AHB1EB|=1;
    GPIOA_MODER|=(0b01<<10);
    volatile uint8_t duty_cycle=0;
    GPIOA_ODR|=(1<<5);
    
    while (1)
    {
        for (volatile uint8_t i=0;i<100;i++){
            if (i<duty_cycle)
                GPIOA_BSRR|=(1<<21);
            else
                GPIOA_BSRR|=(1<<5);
        }
    }
    
}
