#include "stm32f4xx.h"
#include "timer.h"


void tim2_ms_interrupt_init(uint32_t ms){
	// Enable clock access to timer2
	RCC->APB1ENR |= TIM2_EN;
	// Enable counter
	TIM2->CR1 |= COUNT_EN;

	// Clear counter
	TIM2->CNT = 0;
	// Set prescaler
	TIM2->PSC = 1000 - 1;
	// Set auto reload
	TIM2->ARR = 16 * ms;
	// Enable interrupt
	TIM2->DIER |= DIER_UIE;
	// Enable interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

