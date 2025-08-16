#include <stdint.h>
#include "adc.h"
#include "timer.h"
uint32_t res;
int main(void) {
	adc_init();
	tim2_ms_interrupt_init(3000);
	while(1){

	}
}

void timer_callback(void){
	start_conversion();
	res = adc_read();
}

void TIM2_IRQHandler(void){
	// Clear update interrupt flag
	TIM2->SR &=~SR_UIF;
	timer_callback();
}
