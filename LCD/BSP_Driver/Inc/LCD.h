#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f4xx_hal.h"

//#define LCD_BL_GPIO_PORT  			GPIOF			
//#define LCD_BL_GPIO_PIN         	GPIO_PIN_10
//#define LCD_BL_GPIO_CLK_ENABLE();   do{__HAL_RCC_GPIOF_CLK_ENABLE();}while(0)


//#define LCD_BL_Out(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* 设置BL引脚 */


//typedef struct
//{
//    uint16_t width;     /* LCD 宽度 */
//    uint16_t height;    /* LCD 高度 */
//    uint16_t id;        /* LCD ID */
//    uint8_t dir;        /* 横屏还是竖屏控制：0，竖屏；1，横屏。 */
//    uint16_t wramcmd;   /* 开始写gram指令 */
//    uint16_t setxcmd;   /* 设置x坐标指令 */
//    uint16_t setycmd;   /* 设置y坐标指令 */
//} _lcd_dev;


///* 管理LCD重要参数 */
//extern _lcd_dev lcddev;


///* 常用画笔颜色 */
//#define WHITE           0xFFFF      /* 白色 */
//#define BLACK           0x0000      /* 黑色 */
//#define RED             0xF800      /* 红色 */
//#define GREEN           0x07E0      /* 绿色 */
//#define BLUE            0x001F      /* 蓝色 */ 
//#define MAGENTA         0XF81F      /* 品红色/紫红色 = BLUE + RED */
//#define YELLOW          0XFFE0      /* 黄色 = GREEN + RED */
//#define CYAN            0X07FF      /* 青色 = GREEN + BLUE */  

///* 非常用颜色 */
//#define BROWN           0XBC40      /* 棕色 */
//#define BRRED           0XFC07      /* 棕红色 */
//#define GRAY            0X8430      /* 灰色 */ 
//#define DARKBLUE        0X01CF      /* 深蓝色 */
//#define LIGHTBLUE       0X7D7C      /* 浅蓝色 */ 
//#define GRAYBLUE        0X5458      /* 灰蓝色 */ 
//#define LIGHTGREEN      0X841F      /* 浅绿色 */  
//#define LGRAY           0XC618      /* 浅灰色(PANNEL),窗体背景色 */ 
//#define LGRAYBLUE       0XA651      /* 浅灰蓝色(中间层颜色) */ 
//#define LBBLUE          0X2B12      /* 浅棕蓝色(选择条目的反色) */ 

//void lcd_init(void);
//void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
#endif