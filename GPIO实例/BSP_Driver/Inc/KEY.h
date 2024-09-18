#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f4xx_hal.h"

#define KEY0_GPIO_PORT    			GPIOF
#define KEY0_GPIO_PIN				GPIO_PIN_9
#define KEY_GPIO_CLK_ENABLE()       do{__HAL_RCC_GPIOF_CLK_ENABLE();}while(0)

#define KEY1_GPIO_PORT    			GPIOF
#define KEY1_GPIO_PIN				GPIO_PIN_8

#define KEY2_GPIO_PORT    			GPIOF
#define KEY2_GPIO_PIN				GPIO_PIN_7


#define KEY0_READ()		  HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* ��ȡKEY0���� */
#define KEY1_READ()       HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* ��ȡKEY1���� */
#define KEY2_READ()       HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* ��ȡKEY2���� */

#define KEY0_VALUE  	 1              /* KEY0���� */
#define KEY1_VALUE   	 2              /* KEY1���� */
#define KEY2_VALUE    	 3              /* KEY2���� */

void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);
void KEY_test(void);
void KEY_FreeRTOS_test(void);

#endif