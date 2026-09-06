#include <stdint.h>
#include <f446re.h> // Ensure you added 'volatile' in this file!

int clkSetup(void) {
    // 1. Enable Clock
    APB2ENB |= 1; 
    
    // 2. Set Timer values for 1 second (90 MHz clock)
    TIM1_PSC = 8999;
    TIM1_ARR = 9999;
    
    // 3. Load shadow registers (This instantly sets SR to 1!)
    TIM1_EGR |= 1;
    
    // 4. Start Timer
    TIM1_CR1 |= (0b10 << 8) | (1 << 7) | 1;
    
    // 5. Clear the false-start flag caused by EGR
    TIM1_SR = 0; 
    
    while (1) {
        blinkLED(); // Toggle the LED
        
        // Trap the CPU!
        while (!(TIM1_SR & 1)) { 
            // If the compiler STILL ignores volatile, adding this NOP 
            // (No Operation) assembly command forces it to keep the loop
            __asm__("nop"); 
        }
        
        // Clear the status register 
        TIM1_SR = 0; 
    }
}