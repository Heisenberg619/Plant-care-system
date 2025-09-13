#include "i2c_sht40.h"
volatile uint32_t systick_ms = 0;

void i2c1_sht40_write(uint8_t saddr, uint8_t cmd){
	 volatile int tmp;
	 // Wait until bus not busy
	 while(I2C1->SR2 & I2C_SR2_BUSY);
	 // Generate start
	 I2C1->CR1 |= I2C_CR1_START;
	 // Wait until start bit set
	 while (!(I2C1->SR1 & I2C_SR1_SB));

	 // Transmit slave address  + R
	 I2C1->DR = saddr << 1;
	 // Wait until address flag is set
	 while (!(I2C1->SR1 & I2C_SR1_ADDR));
	 // Clear address flag
	 tmp = I2C1->SR2;
	 // Wait until transmitter empty
	 while (!(I2C1->SR1 & I2C_SR1_TXE));
	 // Send command
	 I2C1->DR = cmd;
	 // Generate stop
	 I2C1->CR1 |= CR1_STOP;
}
void i2c1_sht40_read(uint8_t saddr, int n, uint8_t *data) {
    volatile int tmp;
    // Wait until bus not busy
    while (I2C1->SR2 & I2C_SR2_BUSY);
    // Generate start
    I2C1->CR1 |= I2C_CR1_START;
    // Wait until start bit set
    while (!(I2C1->SR1 & I2C_SR1_SB));
    // Send slave address + Read
    I2C1->DR = (saddr << 1) | 1;
    // Wait until addr bit set
    while (!(I2C1->SR1 & I2C_SR1_ADDR));


    I2C1->CR1 |= I2C_CR1_ACK;
    tmp = I2C1->SR2;
    while (n > 0) {
        if (n == 1) {
            I2C1->CR1 &= ~I2C_CR1_ACK;
            I2C1->CR1 |= I2C_CR1_STOP;
        }
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        *data++ = I2C1->DR;
        n--;
    }
}


void i2c_sht40_init(void){
	// Enable clock access
	RCC->AHB1ENR |= GPIOB_EN;
	// Set mode to alternate function
	GPIOB->MODER &= ~(15U << 16);
	GPIOB->MODER |=  (10U << 16);

	// Set alternate function to AF04 (SCL and SDA)
	GPIOB->AFR[1] &= ~(15U << 0);
	GPIOB->AFR[1] |=  (1U << 2);

	GPIOB->AFR[1] &= ~(15U << 4);
	GPIOB->AFR[1] |=  (1U << 6);

	// Set output mode to open drain
	GPIOB->OTYPER |= (3U << 8);
	// Enable pull-up for PB8 and PB9
	GPIOB->PUPDR &=~(15U << 16);
	GPIOB->PUPDR |= (5U << 16);

	// Enable clock access to I2C
	RCC->APB1ENR |= I2C1_EN;
	// Enter reset mode
	I2C1->CR1 |= CR1_SWRST;
	// Come out of reset mode
	I2C1->CR1 &=~CR1_SWRST;

	// Set peripheral clock frequency
	I2C1->CR2 =16;
	// Set I2C mode to standard (100kHz)
	I2C1->CCR = I2C_100KHZ;
	// Set rise time
	I2C1->TRISE = MAX_RISE_TIME;
	// Peripheral enable
	I2C1->CR1 |= CR1_PE;
}

float calculate_temp(uint16_t temp){
	return -45 + 175*((float)temp / 65535.0f);
}
float calculate_hum(uint16_t hum){
	return -6 + 125*((float)hum / 65535.0f);
}
