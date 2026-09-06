#include<stdint.h>
#define RCC 0x40023800
#define RCC_CR *((volatile uint32_t *) (0x00UL+RCC))
#define RCC_PLLCFGR *((volatile uint32_t *) (RCC + 0x04UL))
#define RCC_CFGR *((volatile uint32_t *) (RCC + 0x08UL))
#define FLASH_ACR *((volatile uint32_t *) 0x40023C00)
#define RCC_APB1ENR *((volatile uint32_t *) (RCC+0x40))
#define RCC_APB2ENR *((volatile uint32_t *) (RCC+0x44))
#define RCC_AHB1ENR *((volatile uint32_t *) (RCC+0x30))
#define GPIOA 0x40020000
#define GPIOA_MODER *((volatile uint32_t *) (GPIOA + 0x00))
#define GPIOA_BSRR *((volatile uint32_t *) (GPIOA + 0x18))
#define GPIOA_ODR *((volatile uint32_t *) (GPIOA + 0x14))
#define TIM2 0x40000000
#define TIM2_CR1 *((volatile uint32_t *) (TIM2 + 0x00))
#define TIM2_DIER *((volatile uint32_t *) (TIM2 + 0x0C))
#define TIM2_ARR *((volatile uint32_t *) (TIM2 + 0x2C))
#define TIM2_PSC *((volatile uint32_t *) (TIM2 + 0x28))
#define TIM2_SR *((volatile uint32_t *) (TIM2 + 0x10))
#define NVIC_ISER0 *((volatile uint32_t *) 0xE000E100UL)
void delay(uint16_t);
void pll_setup(void){
	FLASH_ACR &= ~(0xFUL << 0);
	RCC_CFGR &= ~(3UL<<0);
	while (0!=(RCC_CFGR&(3UL<<2)));
	RCC_CR &= ~(1UL<<24);
	while (RCC_CR&(1UL<<25));
	FLASH_ACR |= 0b0101;
	RCC_PLLCFGR = 0;
	RCC_PLLCFGR |= (0b00<<16) | (0b10110100<<6) | (8UL);
	RCC_CFGR &= ~(7UL<<13);
	RCC_CFGR &= ~(7UL<<10);
	RCC_CFGR |= (4UL<<13);
	RCC_CFGR |= (5UL<<10);
	RCC_CR |= (1UL<<24);
        while (!(RCC_CR&(1UL<<25)));
	RCC_CFGR |= (0b10<<0);
	while ((RCC_CFGR&(3UL<<2)) != (2UL<<2));
}
void timer_init(){
	RCC_APB1ENR |= 1UL;
	TIM2_CR1 = 0;
	TIM2_CR1 |= (1UL<<7);
	TIM2_PSC = 89;
	TIM2_ARR = 0xF423F;
	NVIC_ISER0 |= (1UL<<28);
	TIM2_DIER |= (1UL<<0);
	TIM2_CR1 |= (1UL);
}
int main(){
	pll_setup();
	RCC_AHB1ENR |= 1;
	GPIOA_MODER &= ~(3UL<<10);
	GPIOA_MODER |= (1UL<<10);
	timer_init();
	while (1);
	return 0;
}
void TIM2_IRQHandler(){
	TIM2_SR &= ~(1UL<<0);
	GPIOA_ODR ^= (1UL<<5);
}
void delay(uint16_t dly){
	volatile uint16_t i,j;
	for(i=0;i<1000;i++) for(j=0;j<dly;j++);
}

