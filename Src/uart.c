#include "uart.h"


#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define SYS_FREQ  16000000
#define APB1CLK SYS_FREQ

#define UART_BAUDRATE  57600

#define CR1_TE  (1U << 3)
#define CR1_UE  (1U << 13)
#define CR1_RE  (1U << 2)
#define SR_TXE  (1U << 7)
#define SR_RXNE (1U << 5)

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
void uart2_rxtx_init(void){
	/************configure uart gpio pin**********/
	RCC->AHB1ENR |= GPIOAEN; // enable clock access to gpioa
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &=~(1U << 4);// set PA2 mode to alternate function mode

	GPIOA->MODER |= (1U << 7);
	GPIOA->MODER &=~(1U << 6);// set PA3 mode to alternate function mode


	GPIOA->AFR[0] &=~(1U << 11);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 8);// set PA2 alternate function type to UART_TX (AF07)

	GPIOA->AFR[0] &=~(1U << 15);
	GPIOA->AFR[0] |= (1U << 14);
	GPIOA->AFR[0] |= (1U << 13);
	GPIOA->AFR[0] |= (1U << 12);// set PA3 alternate function type to UART_RX (AF07)



	/************configure uart module********/
	RCC->APB1ENR |= UART2EN;// enable clock access to uart
	uart_set_baudrate(USART2,APB1CLK,UART_BAUDRATE);// configure baudrate
	USART2->CR1 = CR1_TE;// configure the transfer direction
	USART2->CR1 |= CR1_RE;//
	USART2->CR1 |= CR1_UE;// enable uart module
}
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {
    return (PeriphClk + (BaudRate/2U)) / BaudRate;
}

void uart2_write(int ch){
	while(!(USART2->SR & SR_TXE));//Make sure the transmit data register is empty
	USART2->DR = (ch & 0xFF);//Write to transmit data register
}

void uart2_write_string(const char *str) {
    while (*str) {
        uart2_write(*str++);
    }
}

void uart2_write_uint(uint32_t num) {
    char buffer[12];
    sprintf(buffer, "%lu", num);
    uart2_write_string(buffer);
}

void uart2_write_float(float num, int decimals) {
    char buffer[32];
    sprintf(buffer, "%.*f", decimals, num);
    uart2_write_string(buffer);
}

void uart2_print_csv(uint32_t time_ms, uint32_t humidity, const char *valve, float temperature, const char *cooler) {
    uart2_write_uint(time_ms);
    uart2_write(',');
    uart2_write_uint(humidity);
    uart2_write(',');
    uart2_write_string(valve);
    uart2_write(',');
    uart2_write_float(temperature, 2);
    uart2_write(',');
    uart2_write_string(cooler);
    uart2_write_string("\r\n");
}
