//#ifndef _FMC_LCD_H_
//#define _FMC_LCD_H_

//#include "stm32f4xx_hal.h"

//#define LCD_BL_GPIO_PORT  			GPIOF			
//#define LCD_BL_GPIO_PIN         	GPIO_PIN_10
//#define LCD_BL_GPIO_CLK_ENABLE();   do{__HAL_RCC_GPIOF_CLK_ENABLE();}while(0)


//#define LCD_BL_Out(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* ����BL���� */

////FMCӳ���ַд�룬�ڶ�Ӧ��ַд���ݣ������ڶ�ӦSRAMд����	    
//#define  CMD_BASE     ((uint32_t)(0x6C000000 | 0x00001FFE))
//#define  DATA_BASE    ((uint32_t)(0x6C000000 | 0x00002000))

//#define LCD_CMD       ( * (uint16_t *) CMD_BASE )
//#define LCD_DATA      ( * (uint16_t *) DATA_BASE)

////ɨ�跽����
//#define  L2R_U2D  0 //������,���ϵ���
//#define  L2R_D2U  1 //������,���µ���
//#define  R2L_U2D  2 //���ҵ���,���ϵ���
//#define  R2L_D2U  3 //���ҵ���,���µ���

//#define  U2D_L2R  4 //���ϵ���,������
//#define  U2D_R2L  5 //���ϵ���,���ҵ���
//#define  D2U_L2R  6 //���µ���,������
//#define  D2U_R2L  7 //���µ���,���ҵ���	 

////��ɫֵ����
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
//	//LCD��������
//	uint16_t  lcd_id;          	//LCD ID
//	uint8_t   dir_flag;        	//�������������ƣ�0��������1������
//	uint16_t  lcd_width;       	//LCD�Ŀ��
//	uint16_t  lcd_height;       //LCD�ĸ߶�
//	uint16_t  write_gramcmd;	//дgramָ��
//	uint16_t  setxcmd;		    //����x����ָ��
//	uint16_t  setycmd;		    //����y����ָ��	
//	
//}LCD_HandleTypeDef;

//void LCD_Init(void);
//void LCD_DrawPoint(uint16_t x,uint16_t y);
//void LCD_Color_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

//#endif