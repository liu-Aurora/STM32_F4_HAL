 #ifndef _SPI_H_
 #define _SPI_H_
 
 #include "stm32f4xx_hal.h"
 
 #define SPI_CS_GPIO_PORT                   GPIOG
 #define SPI_CS_GPIO_PIN                   GPIO_PIN_8
 #define SPI_CS_GPIO_RCC_CLK_ENABLE        do{__HAL_RCC_GPIOG_CLK_ENABLE();}while(0)
												
 #define SPI_SCK_GPIO_PORT                  GPIOB
 #define SPI_SCK_GPIO_PIN                  GPIO_PIN_3
 #define SPI_SCK_GPIO_RCC_CLK_ENABLE       do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)
 
 #define SPI_MOSI_GPIO_PORT                 GPIOB
 #define SPI_MOSI_GPIO_PIN                 GPIO_PIN_5
 #define SPI_MOSI_GPIO_RCC_CLK_ENABLE      do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)
 
 #define SPI_MISO_GPIO_PORT                 GPIOB
 #define SPI_MISO_GPIO_PIN                 GPIO_PIN_4
 #define SPI_MISO_GPIO_RCC_CLK_ENABLE      do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)
 
 
 #define SPI_CS_OUT(x)   	do{x ? \
							HAL_GPIO_WritePin(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,GPIO_PIN_SET):\
				            HAL_GPIO_WritePin(SPI_CS_GPIO_PORT,SPI_CS_GPIO_PIN,GPIO_PIN_RESET);\
							}while(0)

 #define SPI_SCK_OUT(x)   	do{x ? \
							HAL_GPIO_WritePin(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN,GPIO_PIN_SET):\
				            HAL_GPIO_WritePin(SPI_SCK_GPIO_PORT,SPI_SCK_GPIO_PIN,GPIO_PIN_RESET);\
							}while(0)
 
#define SPI_MOSI_OUT(x)   	do{x ? \
							HAL_GPIO_WritePin(SPI_MOSI_GPIO_PORT,SPI_MOSI_GPIO_PIN,GPIO_PIN_SET):\
				            HAL_GPIO_WritePin(SPI_MOSI_GPIO_PORT,SPI_MOSI_GPIO_PIN,GPIO_PIN_RESET);\
							}while(0)

 #define SPI_MISO_OUT(x)   	do{x ? \
							HAL_GPIO_WritePin(SPI_MISO_GPIO_PORT,SPI_MISO_GPIO_PIN,GPIO_PIN_SET):\
				            HAL_GPIO_WritePin(SPI_MISO_GPIO_PORT,SPI_MISO_GPIO_PIN,GPIO_PIN_RESET);\
							}while(0) 
 

#define SPI_MISO_READ()		HAL_GPIO_ReadPin(SPI_MISO_GPIO_PORT,SPI_MISO_GPIO_PIN)
				
 #endif