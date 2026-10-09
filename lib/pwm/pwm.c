#include "pwm.h"

#define PIN_CH1 6
#define PIN_CH2 7
#define PIN_CH3 0
#define PIN_CH4 1


void pwm_init(uint8_t canal, uint32_t frec){
    switch(canal){
        case 1:
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
        RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
        GPIOA->CRL &=~ (0xF<<(PIN_CH1)*4);
        GPIOA->CRL |= (0xB<<(PIN_CH1)*4);
        TIM3->CCMR1 &=~ (0xb111<<4);
        TIM3->CCMR1 |= (0xb110<<4);
        TIM3 -> CCER |= TIM_CCER_CC1E;
        break;
        case 2:
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
        RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
        GPIOA->CRL &=~ (0xF<<(PIN_CH2)*4);
        GPIOA->CRL |= (0xB<<(PIN_CH2)*4);
        TIM3->CCMR1 &=~ (0xb111<<12);
        TIM3->CCMR1 |= (0xb110<<12);
        TIM3 -> CCER |= TIM_CCER_CC2E;
        break;
        case 3:
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
        RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
        GPIOB->CRL &=~ (0xF<<(PIN_CH3)*4);
        GPIOB->CRL |= (0xB<<(PIN_CH3)*4);
        TIM3->CCMR2 &=~ (0xb111<<4);
        TIM3->CCMR2 |= (0xb110<<4);
        TIM3 -> CCER |= TIM_CCER_CC3E;
        break;
        case 4:
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
        RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
        GPIOA->CRL &=~ (0xF<<(PIN_CH4)*4);
        GPIOA->CRL |= (0xB<<(PIN_CH4)*4);
        TIM3->CCMR2 &=~ (0xb111<<12);
        TIM3->CCMR2 |= (0xb110<<12);
        TIM3 -> CCER |= TIM_CCER_CC4E;
    }
TIM3-> PSC=7;
TIM3 -> ARR=(1000000/frec)-1;
TIM3->EGR|=TIM_EGR_UG;
TIM3->CR1|=TIM_CR1_CEN;
}

void pwm(uint8_t canal , uint8_t duty){
    if(duty>100) duty=100;

    if(canal==1) TIM3->CCR1 = (TIM3->ARR+1)*(duty/100);
    else if(canal==2) TIM3->CCR2 = (TIM3->ARR+1)*(duty/100);
    else if(canal==3) TIM3->CCR3 = (TIM3->ARR+1)*(duty/100);
    else if(canal==4) TIM3->CCR4 = (TIM3->ARR+1)*(duty/100);
}