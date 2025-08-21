#include <stdint.h>
#include "adc.h"
#include "timer.h"
#include "i2c_sht40.h"

volatile uint8_t arr[6];
volatile float temperature = 0.0f;
volatile uint16_t temp=0;
volatile uint16_t hum=0;
volatile float x=0.0f;
volatile float humidity = 0.0f;
int main(void) {
	SCB->CPACR |= 0x00F00000;
    adc_init();
    tim2_ms_interrupt_init(3000);
    i2c_sht40_init();
    while (1) {

    }
}
void callback(void){
	i2c1_sht40_write(DEVICE_ADDR, 0xFD);
	delay_ms(10);
	i2c1_sht40_read(DEVICE_ADDR,6,arr);
	temp = (arr[0] << 8) | arr[1];
	hum = (arr[3] << 8) | arr[4];
	temperature = calculate_temp(temp);
	humidity = calculate_hum(hum);
	if(temperature > 30.0f)GPIOA->ODR |= (1U << 1);
	else GPIOA->ODR &=~(1U << 1);
}
void TIM2_IRQHandler(void) {
    TIM2->SR &= ~SR_UIF;
    callback();
}
