#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "stm32f4xx_hal.h"

#define BUZZER_GPIO_PORT	   		GPIOG
#define BUZZER_GPIO_PIN        		GPIO_PIN_7
#define BUZZER_GPIO_CLK_ENABLE()  	do{__HAL_RCC_GPIOG_CLK_ENABLE();}while(0)

#define BUZZER_Out(x)	do{ x?\
							HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN,GPIO_PIN_SET):\
	                        HAL_GPIO_WritePin(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN,GPIO_PIN_RESET);\
							}while(0)    

void Buzzer_Init(void);							
void Buzzer_test(void);							
void Buzzer_FreeRTOS_test(void);
							
#endif
