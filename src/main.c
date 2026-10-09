#include "stm32f103xb.h"
#include "ADC.h"
#include "pwm.h"

int conversion=0;

int main(void){
    adc_init();
    pwm_init(1, 1000);
    while(1){
        conversion = adc_read(1);
        int duty=conversion*100/4095;
        pwm(1,duty);
    }

}