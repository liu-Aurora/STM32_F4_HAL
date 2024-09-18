#ifndef _I2C_H_
#define _I2C_H_

#include "stm32f4xx_hal.h"

#define I2C_SDA_GPIO_PORT 			GPIOC
#define I2C_SDA_GPIO_PIN            GPIO_PIN_6
#define I2C_SDA_GPIO_CLE_ENABLE()	do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)


#define I2C_SCL_GPIO_PORT 			GPIOC
#define I2C_SCL_GPIO_PIN            GPIO_PIN_7
#define I2C_SCL_GPIO_CLE_ENABLE()	do{__HAL_RCC_GPIOC_CLK_ENABLE();}while(0)

#define I2C_SCL(x)		do{ x? \
							HAL_GPIO_WritePin(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN,GPIO_PIN_SET):\
	                        HAL_GPIO_WritePin(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN,GPIO_PIN_RESET);\
						}while(0)

						
#define I2C_SDA(x) 		do{ x? \
							HAL_GPIO_WritePin(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN,GPIO_PIN_SET):\
                            HAL_GPIO_WritePin(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN,GPIO_PIN_RESET);\
						}while(0)

#define I2C_READ() 	  HAL_GPIO_ReadPin(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)
		
						
						
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Wait_Ack(void);
void I2C_Send_Ack(void);
void I2C_Send_Byte(uint8_t data);
uint8_t I2C_Read_Byte(void);	

#endif