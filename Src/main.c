#include <stdint.h>
#include "adc.h"
#include "timer.h"
#include "i2c_sht40.h"
#include "uart.h"

uint16_t interrupt=0;
volatile uint16_t time_ms = 0;

void gpio_init(void){
	// Enable clock access for GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
	// Set PC4 and PC8 as output
	GPIOC->MODER &= ~((0b11 << 16) | (0b11 << 8));
	GPIOC->MODER |=  ((0b01 << 16) | (0b01 << 8));
}
void update_actuators(float temperature, uint16_t moisture, char *cooler, char *valve){
	if(temperature >= 31.0f){
		GPIOC->ODR |= (1U << 4);
		cooler[0] = 'O';cooler[1] = 'N';cooler[2] = ' ';
	}
	else if(temperature <= 30.0f){
		GPIOC->ODR &=~(1U << 4);
		cooler[0] = 'O';cooler[1] = 'F';cooler[2] = 'F';
	}
	if(moisture >1800){
		GPIOC->ODR |= (1U << 8);
		valve[0] = 'O';valve[1] = 'N';valve[2] = ' ';
	}
	else{
		GPIOC->ODR &= ~(1U << 8);
		valve[0] = 'O';valve[1] = 'F';valve[2] = 'F';
	}
}

int main(void) {
	// Enable FPU
	SCB->CPACR |= 0x00F00000;

    adc_init();
    tim2_ms_interrupt_init(1000);
    i2c_sht40_init();
    uart2_rxtx_init();
    gpio_init();

    char valve[3] = "OFF";
    char cooler[3] = "OFF";
    uint8_t arr[6];

    while (1) {
    	if(interrupt){
    		// Read temperature
    		i2c1_sht40_write(DEVICE_ADDR, 0xFD);
    		delay_ms(10);
    		i2c1_sht40_read(DEVICE_ADDR,6,arr);

    		// Read moisture
    		uint16_t raw_temp = (arr[0] << 8) | arr[1];
    		float temperature = calculate_temp(raw_temp);

    		start_conversion();
    		uint16_t moisture = adc_read();
    		update_actuators(temperature,moisture, cooler, valve);
    		uart2_print_csv(time_ms, moisture, valve, temperature, cooler);

    		interrupt = 0;
    	}
    }
}
void TIM2_IRQHandler(void) {
    TIM2->SR &= ~SR_UIF;
    interrupt=1;
}
