#include<stdint.h>

#define RCC_BASE 0x40023800UL
#define RCC_AHB1ENR (*(volatile uint32_t *) (RCC_BASE + 0x30UL))
#define RCC_CR (*(volatile uint32_t *) (RCC_BASE + 0x00))
#define RCC_PLLCNFG (*(volatile uint32_t *) (RCC_BASE + 0x04))
#define RCC_CFGR (*(volatile uint32_t *) (RCC_BASE + 0x08))

#define GPIOA_BASE 0x40020000UL
#define GPIOA_MODER (*(volatile uint32_t *) (GPIOA_BASE + 0x00UL))
#define GPIOA_ODR (*(volatile uint32_t *) (GPIOA_BASE + 0x14UL))

#define FLASH_ITF_BASE 0x40023C00UL
#define FLASH_ACR (*(volatile uint32_t *) (FLASH_ITF_BASE + 0x00))

void delay(int);


void clock_init(){
	RCC_CFGR &= (3UL<<0);
	while((RCC_CR)&(3UL<<2) != 0);
	
	RCC_CR &= ~ (1UL << 24);
	while((RCC_CR)&(1UL<<25));
	
	FLASH_ARC &= ~(0xFUL << 0);
	FLASH_ARC |= (5UL << 0);
	
	RCC_PLLCFGR = 0;
	RCC_PLLCFGR |= (2b00<<16) | (6b000100) | (9b001011010<<6);
	RCC_CR |= (1<<0);
	while(!(RCC_CR)&(1b1<<1));
	RCC_CR |= (1<<16);
	while(!(RCC_CR)&(1b1<<16));
}

int main(void){
	RCC_AHB1ENR|=1;
	GPIOA_MODER&=~(3UL<<10);
	GPIOA_MODER|=(1UL<<10);
	while(1){
		GPIOA_ODR|=(1<<5);
		delay(500);
		GPIOA_ODR&=~(1<<5);
		delay(500);
	}
}


void delay(int a){
	for(int n=0;n<=1000;n++)
		for(volatile int j=0;j<a;j++);
}
