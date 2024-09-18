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
#define GPIO_DATA8080_PIN               GPIO_PIN_All                                  /* 16个IO都用到 */
#define GPIO_DATA8080_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

/* LCD 端口控制函数定义 */
/* 利用操作寄存器的方式控制IO引脚提高屏幕的刷新率 */
#define WR8080_Out(x)       GPIO_WR8080_PORT->BSRR = GPIO_WR8080_PIN << (16 * (!x))     /* 设置WR引脚 */
#define RD8080_Out(x)       GPIO_RD8080_PORT->BSRR = GPIO_RD8080_PIN << (16 * (!x))     /* 设置RD引脚 */
#define CS8080_Out(x)       GPIO_CS8080_PORT->BSRR = GPIO_CS8080_PIN << (16 * (!x))     /* 设置CS引脚 */
#define RS8080_Out(x)       GPIO_RS8080_PORT->BSRR = GPIO_RS8080_PIN << (16 * (!x))     /* 设置RS引脚 */

#define DATA8080_OUT(x) 	GPIO_DATA8080_PORT->ODR = x                                 /* 写B0~B15引脚 */
#define LCD_DATA_IN    		GPIO_DATA8080_PORT->IDR                                     /* 读B0~B15引脚 */


#endif