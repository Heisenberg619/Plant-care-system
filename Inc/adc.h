/*
 * adc.h
 *
 *  Created on: Aug 16, 2025
 *      Author: Korisnik
 */

#ifndef ADC_H_
#define ADC_H_
#include "stm32f4xx.h"
void adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
