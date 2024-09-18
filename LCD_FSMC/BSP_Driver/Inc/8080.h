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
#define DATA1_GPIO_PIN               GPIOD_PIN15                                  /* 16个IO都用到 */
#define DATA1_GPIO__CLK_ENABLE() 	 do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */


/* LCD 端口控制函数定义 */
/* 利用操作寄存器的方式控制IO引脚提高屏幕的刷新率 */
#define WR8080_Out(x)       WR8080_GPIO_PORT->BSRR = WR8080_GPIO_PIN << (16 * (!x))     /* 设置WR引脚 */
#define RD8080_Out(x)       RS8080_GPIO_PORT->BSRR = RS8080_GPIO_PIN << (16 * (!x))     /* 设置RD引脚 */
#define CS8080_Out(x)       CS8080_GPIO_PORT->BSRR = CS8080_GPIO_PIN << (16 * (!x))     /* 设置CS引脚 */
#define RS8080_Out(x)       RS8080_GPIO_PORT->BSRR = RS8080_GPIO_PIN << (16 * (!x))     /* 设置RS引脚 */

#define DATA8080_OUT(x) 	DATA8080_GPIO_PORT->ODR = x                                 /* 写B0~B15引脚 */
#define LCD_DATA_IN()    		DATA8080_GPIO_PORT->IDR                                     /* 读B0~B15引脚 */

void WR_Data_8080(uint16_t data);
void WR_Reg_8008(uint16_t command);

#endif