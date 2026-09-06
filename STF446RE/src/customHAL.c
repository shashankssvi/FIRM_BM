/* Bitmasking & Register Manipulation

    SET_BIT(reg, bit): Sets a specific bit to 1.
    CLEAR_BIT(reg, bit): Sets a specific bit to 0.
    TOGGLE_BIT(reg, bit): Flips the bit state.
*/

#include<stdint.h>
#define SET_BIT(reg,bit) (*(volatile uint32_t*)reg)|=(1<<bit)
#define CLEAR_BIT(reg,bit) (*(volatile uint32_t*)reg)&=~(1<<bit)
#define TOGGLE_BIT(reg,bit) (*(volatile uint32_t*)reg)^=~(1<<bit)