#ifndef ADC_H
#define ADC_H

#include "stm32f103xb.h"
#include "stdint.h"

void adc_init(void);
int adc_read(unsigned int canal);


#endif