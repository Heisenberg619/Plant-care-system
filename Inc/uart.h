/*
 * uart.h
 *
 *  Created on: 6. avg 2025.
 *      Author: Korisnik
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#endif /* UART_H_ */



int __io_putchar(int ch);
void uart2_rxtx_init(void);
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);
char uart2_read();
void uart2_write_string(const char *str);
void uart2_write_uint(uint32_t num);
void uart2_write_float(float num, int decimals);
void uart2_print_csv(uint32_t time_ms, uint32_t humidity, const char *valve, float temperature, const char *cooler);
