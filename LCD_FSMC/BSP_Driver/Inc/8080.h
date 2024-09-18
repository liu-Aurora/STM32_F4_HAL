#ifndef _8080_H_
#define _8080_H_

#include "stm32f4xx_hal.h"

#define CS8080_GPIO_PORT  			GPIOG			
#define CS8080_GPIO_PIN         	GPIO_PIN_12
#define CS8080_GPIO_CLK_ENABLE()    do{__HAL_RCC_GPIOG_CLK_ENABLE();}while(0)

#define WR8080_GPIO_PORT  			GPIOD			
#define WR8080_GPIO_PIN         	GPIO_PIN_5
#define WR8080_GPIO_CLK_ENABLE()    do{__HAL_RCC_GPIOD_CLK_ENABLE();}while(0)

#define RS8080_GPIO_PORT  			GPIOG			
#define RS8080_GPIO_PIN         	GPIO_PIN_2
#define RS8080_GPIO_CLK_ENABLE()    do{__HAL_RCC_GPIOG_CLK_ENABLE();}while(0)

#define RD8080_GPIO_PORT  			GPIOD			
#define RD8080_GPIO_PIN         	GPIO_PIN_4
#define RD8080_GPIO_CLK_ENABLE()    do{__HAL_RCC_GPIOD_CLK_ENABLE();}while(0)


#define DATA1_GPIO_PORT              GPIOD
#define DATA1_GPIO_PIN               GPIOD_PIN15                                  /* 16��IO���õ� */
#define DATA1_GPIO__CLK_ENABLE() 	 do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */


/* LCD �˿ڿ��ƺ������� */
/* ���ò����Ĵ����ķ�ʽ����IO���������Ļ��ˢ���� */
#define WR8080_Out(x)       WR8080_GPIO_PORT->BSRR = WR8080_GPIO_PIN << (16 * (!x))     /* ����WR���� */
#define RD8080_Out(x)       RS8080_GPIO_PORT->BSRR = RS8080_GPIO_PIN << (16 * (!x))     /* ����RD���� */
#define CS8080_Out(x)       CS8080_GPIO_PORT->BSRR = CS8080_GPIO_PIN << (16 * (!x))     /* ����CS���� */
#define RS8080_Out(x)       RS8080_GPIO_PORT->BSRR = RS8080_GPIO_PIN << (16 * (!x))     /* ����RS���� */

#define DATA8080_OUT(x) 	DATA8080_GPIO_PORT->ODR = x                                 /* дB0~B15���� */
#define LCD_DATA_IN()    		DATA8080_GPIO_PORT->IDR                                     /* ��B0~B15���� */

void WR_Data_8080(uint16_t data);
void WR_Reg_8008(uint16_t command);

#endif