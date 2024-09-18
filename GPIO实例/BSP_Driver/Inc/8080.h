#ifndef _8080_H_
#define _8080_H_

#include "stm32f4xx_hal.h"

#define GPIO_CS8080_PORT  			GPIOG			
#define GPIO_CS8080_PIN         	GPIO_PIN_12
#define CS8080_GPIO_CLK_ENABLE      do{__HAL_RCC_GPIOG_CLK_ENABLE()}while(0)

#define GPIO_WR8080_PORT  			GPIOD			
#define GPIO_WR8080_PIN         	GPIO_PIN_5
#define WR8080_GPIO_CLK_ENABLE      do{__HAL_RCC_GPIOD_CLK_ENABLE()}while(0)

#define GPIO_RS8080_PORT  			GPIOG			
#define GPIO_RS8080_PIN         	GPIO_PIN_2
#define RS8080_GPIO_CLK_ENABLE      do{__HAL_RCC_GPIOG_CLK_ENABLE()}while(0)

#define GPIO_RD8080_PORT  			GPIOD			
#define GPIO_RD8080_PIN         	GPIO_PIN_4
#define RD8080_GPIO_CLK_ENABLE      do{__HAL_RCC_GPIOD_CLK_ENABLE()}while(0)

#define GPIO_DATA8080_PORT              GPIOD
#define GPIO_DATA8080_PIN               GPIO_PIN_All                                  /* 16��IO���õ� */
#define GPIO_DATA8080_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */

/* LCD �˿ڿ��ƺ������� */
/* ���ò����Ĵ����ķ�ʽ����IO���������Ļ��ˢ���� */
#define WR8080_Out(x)       GPIO_WR8080_PORT->BSRR = GPIO_WR8080_PIN << (16 * (!x))     /* ����WR���� */
#define RD8080_Out(x)       GPIO_RD8080_PORT->BSRR = GPIO_RD8080_PIN << (16 * (!x))     /* ����RD���� */
#define CS8080_Out(x)       GPIO_CS8080_PORT->BSRR = GPIO_CS8080_PIN << (16 * (!x))     /* ����CS���� */
#define RS8080_Out(x)       GPIO_RS8080_PORT->BSRR = GPIO_RS8080_PIN << (16 * (!x))     /* ����RS���� */

#define DATA8080_OUT(x) 	GPIO_DATA8080_PORT->ODR = x                                 /* дB0~B15���� */
#define LCD_DATA_IN    		GPIO_DATA8080_PORT->IDR                                     /* ��B0~B15���� */


#endif