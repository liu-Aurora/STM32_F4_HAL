#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f4xx_hal.h"

//#define LCD_BL_GPIO_PORT  			GPIOF			
//#define LCD_BL_GPIO_PIN         	GPIO_PIN_10
//#define LCD_BL_GPIO_CLK_ENABLE();   do{__HAL_RCC_GPIOF_CLK_ENABLE();}while(0)


//#define LCD_BL_Out(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* ����BL���� */


//typedef struct
//{
//    uint16_t width;     /* LCD ��� */
//    uint16_t height;    /* LCD �߶� */
//    uint16_t id;        /* LCD ID */
//    uint8_t dir;        /* ���������������ƣ�0��������1�������� */
//    uint16_t wramcmd;   /* ��ʼдgramָ�� */
//    uint16_t setxcmd;   /* ����x����ָ�� */
//    uint16_t setycmd;   /* ����y����ָ�� */
//} _lcd_dev;


///* ����LCD��Ҫ���� */
//extern _lcd_dev lcddev;


///* ���û�����ɫ */
//#define WHITE           0xFFFF      /* ��ɫ */
//#define BLACK           0x0000      /* ��ɫ */
//#define RED             0xF800      /* ��ɫ */
//#define GREEN           0x07E0      /* ��ɫ */
//#define BLUE            0x001F      /* ��ɫ */ 
//#define MAGENTA         0XF81F      /* Ʒ��ɫ/�Ϻ�ɫ = BLUE + RED */
//#define YELLOW          0XFFE0      /* ��ɫ = GREEN + RED */
//#define CYAN            0X07FF      /* ��ɫ = GREEN + BLUE */  

///* �ǳ�����ɫ */
//#define BROWN           0XBC40      /* ��ɫ */
//#define BRRED           0XFC07      /* �غ�ɫ */
//#define GRAY            0X8430      /* ��ɫ */ 
//#define DARKBLUE        0X01CF      /* ����ɫ */
//#define LIGHTBLUE       0X7D7C      /* ǳ��ɫ */ 
//#define GRAYBLUE        0X5458      /* ����ɫ */ 
//#define LIGHTGREEN      0X841F      /* ǳ��ɫ */  
//#define LGRAY           0XC618      /* ǳ��ɫ(PANNEL),���屳��ɫ */ 
//#define LGRAYBLUE       0XA651      /* ǳ����ɫ(�м����ɫ) */ 
//#define LBBLUE          0X2B12      /* ǳ����ɫ(ѡ����Ŀ�ķ�ɫ) */ 

//void lcd_init(void);
//void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
#endif