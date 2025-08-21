
#ifndef I2C_SHT40_H_
#define I2C_SHT40_H_

#include "stm32f4xx.h"

#define GPIOB_EN       (1U << 1)
#define I2C1_EN        (1U << 21)
#define CR1_SWRST      (1U << 15)
#define I2C_100KHZ        80
#define MAX_RISE_TIME     17
#define CR1_PE         (1U << 0)

#define SR2_BUSY       (1U << 1)
#define CR1_START      (1U << 8)
#define SR1_START_BIT  (1U << 1)
#define SR1_TXE        (1U << 7)
#define SR1_ADDRESS    (1U << 1)
#define CR1_ACK        (1U << 10)
#define CR1_STOP       (1U << 9)
#define SR1_RXNE       (1U << 6)
#define DEVICE_ADDR     (0x44)
#define DATA_START_ADDR (0xFD)

void i2c_sht40_init(void);
void i2c1_sht40_read(uint8_t saddr, int n, uint8_t *data);
void i2c1_sht40_write(uint8_t saddr, uint8_t cmd);
void I2C1read(uint8_t saddr, uint8_t maddr, int n, uint8_t *data);
float sht40_read_temp(void);

float calculate_temp(uint16_t temp);
float calculate_hum(uint16_t hum);
#endif /* I2C_SHT40_H_ */
