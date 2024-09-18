//#ifndef _FMC_LCD_H_
//#define _FMC_LCD_H_

//#include "stm32f4xx_hal.h"

//#define LCD_BL_GPIO_PORT  			GPIOF			
//#define LCD_BL_GPIO_PIN         	GPIO_PIN_10
//#define LCD_BL_GPIO_CLK_ENABLE();   do{__HAL_RCC_GPIOF_CLK_ENABLE();}while(0)


//#define LCD_BL_Out(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* 设置BL引脚 */

////FMC映射地址写入，在对应地址写数据，就是在对应SRAM写数据	    
//#define  CMD_BASE     ((uint32_t)(0x6C000000 | 0x00001FFE))
//#define  DATA_BASE    ((uint32_t)(0x6C000000 | 0x00002000))

//#define LCD_CMD       ( * (uint16_t *) CMD_BASE )
//#define LCD_DATA      ( * (uint16_t *) DATA_BASE)

////扫描方向定义
//#define  L2R_U2D  0 //从左到右,从上到下
//#define  L2R_D2U  1 //从左到右,从下到上
//#define  R2L_U2D  2 //从右到左,从上到下
//#define  R2L_D2U  3 //从右到左,从下到上

//#define  U2D_L2R  4 //从上到下,从左到右
//#define  U2D_R2L  5 //从上到下,从右到左
//#define  D2U_L2R  6 //从下到上,从左到右
//#define  D2U_R2L  7 //从下到上,从右到左	 

////颜色值定义
//#define  WHITE        0xFFFF
//#define  BLACK        0x0000	
//#define  RED          0xF800
//#define  GREEN        0x07E0
//#define  BLUE         0x001F 
//#define  BRED         0XF81F
//#define  GRED 			  0XFFE0
//#define  GBLUE			  0X07FF
//#define  BROWN 			  0XBC40  
//#define  BRRED 			  0XFC07  
//#define  GRAY  			  0X8430  
//#define  MAGENTA      0xF81F
//#define  CYAN         0x7FFF
//#define  YELLOW       0xFFE0

//typedef struct
//{
//	//LCD驱动参数
//	uint16_t  lcd_id;          	//LCD ID
//	uint8_t   dir_flag;        	//横屏与竖屏控制：0，竖屏；1，横屏
//	uint16_t  lcd_width;       	//LCD的宽度
//	uint16_t  lcd_height;       //LCD的高度
//	uint16_t  write_gramcmd;	//写gram指令
//	uint16_t  setxcmd;		    //设置x坐标指令
//	uint16_t  setycmd;		    //设置y坐标指令	
//	
//}LCD_HandleTypeDef;

//void LCD_Init(void);
//void LCD_DrawPoint(uint16_t x,uint16_t y);
//void LCD_Color_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

//#endif