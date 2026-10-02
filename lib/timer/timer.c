#include "timer.h"

volatile int timer_overflow=0;
void timer_init(){
RCC -> APB1ENR|=RCC_APB1ENR_TIM2EN;
TIM2-> CR1 &=~ TIM_CR1_CEN;
TIM2 -> PSC=7;
TIM2 -> ARR = 0xFFFF;
TIM2 -> CNT=0;
TIM2 -> DIER|= TIM_DIER_UIE; 
TIM2 -> EGR|= TIM_EGR_UG;
TIM2 -> SR &=~ TIM_SR_UIF;
NVIC_EnableIRQ(TIM2_IRQn);
TIM2 -> CR1 |= TIM_CR1_CEN;
}

uint32_t timer_millis(){
    (timer_overflow + TIM2 -> CNT)/1000000;
    return; 
}

void TIM2_IRQHandler(){
    if (TIM2 -> SR &= TIM_SR_UIF){
        timer_overflow =+ 0xFFFF;
    }
}

void delay_init(){
RCC -> APB1ENR|=RCC_APB1ENR_TIM2EN;
TIM2-> CR1 &=~ TIM_CR1_CEN;
TIM2 -> PSC=7;
TIM2 -> ARR = 0xFFFF;
TIM2 -> CNT=0;
TIM2 -> EGR|= TIM_EGR_UG;
TIM2 -> SR &=~ TIM_SR_UIF;

}

void delay_us(uint32_t us){
    TIM2 -> CR1 |= TIM_CR1_CEN;
    TIM2 -> CNT=0; 
    volatile int t_actual=0;
    volatile int t_inicial = TIM2 -> CNT;
        while(t_actual > us){
            t_actual=(TIM2 -> CNT - t_inicial);
        }
    TIM2 -> CNT=0; 
    TIM2 -> CR1 &=~ TIM_CR1_CEN;
}

void delay_ms(uint32_t ms){
    TIM2 -> CR1 |= TIM_CR1_CEN;
    TIM2 -> CNT=0; 
        volatile int t_actual=0;
        volatile int t_inicial = (TIM2 -> CNT)/1000;
            while(t_actual > ms){
            t_actual=((TIM2 -> CNT)/1000 - t_inicial);
        }
    TIM2 -> CNT=0; 
    TIM2 -> CR1 &=~ TIM_CR1_CEN;
}