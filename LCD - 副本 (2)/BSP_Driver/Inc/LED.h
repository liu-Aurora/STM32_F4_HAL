#ifndef _LED_H_
#define _LED_H_

#include "stm32f4xx_hal.h"

#define LED0_GPIO_PORT  			GPIOE
#define LED0_GPIO_PIN   			GPIO_PIN_3
#define LED0_GPIO_CLK_ENABLE()      do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0) 


#define LED1_GPIO_PORT  			GPIOE
#define LED1_GPIO_PIN   			GPIO_PIN_4
#define LED1_GPIO_CLK_ENABLE()       do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0) 

#define LED2_GPIO_PORT  			GPIOG
#define LED2_GPIO_PIN   			GPIO_PIN_9
#define LED2_GPIO_CLK_ENABLE()       do{__HAL_RCC_GPIOG_CLK_ENABLE();}while(0) 


#define LED0_Out(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)          


#define LED1_Out(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)  

#define LED2_Out(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)

#define LED0_TOGGLE()   do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)     
#define LED1_TOGGLE()   do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)   				  
#define LED2_TOGGLE()   do{ HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN); }while(0)  				  
				  
			
void LED_Init(void);
void LED_test(void);
void LED_FreeRTOS_test(void);

#endif