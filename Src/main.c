#include <stdint.h>
#include "adc.h"


int main(void) {
	adc_init();
	start_conversion();
	uint32_t res;
	while(1){
		res = adc_read();
	}
}
