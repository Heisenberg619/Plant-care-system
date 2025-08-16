

#include "adc.h"
#define ADC1_EN (1U << 8)
#define GPIOC_EN (1U << 2)
#define PC2_CH12 (12U << 0)
#define ADC_ON (1U << 0)
#define ADC_CONT (1U << 1)
#define ADC_START (1U << 30)
#define ADC_EOC (1U << 1)
void adc_init(void){
	// Enable clock access to GPIOC
	RCC->AHB1ENR |= GPIOC_EN;
	// Set GPIOC mode to analog
	GPIOC->MODER |= (1U << 5);
	GPIOC->MODER |= (1U << 4);
	// Enable clock access to ADC
	RCC->APB2ENR |= ADC1_EN;
	// Set number of conversions to 1
	ADC1->SQR1 &= ~(15U << 20);
	// Set conversion 1 to channel 12
	ADC1->SQR3 &= ~(15U << 0);
	ADC1->SQR3 |= PC2_CH12;
	// Enable ADC
	ADC1->CR2 |= ADC_ON;
}

void start_conversion(void){
	// Enable continuous conversion
	ADC1->CR2 |= ADC_CONT;
	// Start conversion
	ADC1->CR2 |= ADC_START;
}
uint32_t adc_read(void){
	while(!(ADC1->SR & ADC_EOC));
	return ADC1->DR;
}

