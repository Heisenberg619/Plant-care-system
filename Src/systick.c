#include "stm32f4xx.h"
#include "systick.h"


#define SYSTICK_LOAD_VAL 16000
#define CTRL_ENABLE  (1U << 0)
#define CTRL_CLKSRC  (1U << 2)
#define CTRL_COUNTFLAG  (1U << 16)

void delay_ms(int delay){
	// Reload with number of clocks per millisecond
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear systick current value register
	SysTick->VAL = 0;

	// Enable systick and select internal clock source
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;

	for(int i=0;i<delay;i++){
		// Wait until the count flag is set
		while(!(SysTick->CTRL & CTRL_COUNTFLAG));
	}
	SysTick->CTRL = 0;
}
