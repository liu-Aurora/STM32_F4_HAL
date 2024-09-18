#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f4xx_hal.h"

#define SYSCLK 168    //ϵͳʱ��

void delay_init();
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif