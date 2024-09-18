#include "led.h"
#include "beep.h"
#include "key.h"
#include "lcd.h"

/*********************************************************************************
*********************�������� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����5 LCD��ʾ������main()                                            *
* �ļ�������LCD��ʾʵ��                                                          *
* �������ڣ�2018.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������������LED���������������                                          *
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{ 
	u8 i=1;
  u16 num;
	
  HAL_Init();                    	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init();     //��ʱ������ʼ��
	LED_Init();				//LED��ʼ��
	BEEP_Init();      //��������ʼ��
	KEY_Init();       //������ʼ��
 	LCD_Init();           //��ʼ��LCD FSMC�ӿں���ʾ����
	BRUSH_COLOR=RED;      //���û�����ɫΪ��ɫ
	
	LCD_DisplayString(10,10,24,"Illuminati STM32");	
	LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"4.TFTLCD TEST");
	LCD_DisplayString(50,110,16,"KEY0:Screen Test");	
	LCD_DisplayString(50,130,16,"KEY1:Number Test");				
  
	while(1) 
	{		 
		key_scan(0);
		
		if(keydown_data==KEY0_DATA)
		  {	
				while(i)
				 {	
				    switch(i)
							{							
								case 1:LCD_Clear(BLACK);break;
								case 2:LCD_Clear(BLUE);break;
								case 3:LCD_Clear(RED);break;
								case 4:LCD_Clear(MAGENTA);break;
								case 5:LCD_Clear(GREEN);break;
								case 6:LCD_Clear(CYAN);break; 
								case 7:LCD_Clear(YELLOW);break;
								case 8:LCD_Clear(BRRED);break;
								case 9:LCD_Clear(GRAY);break;
								case 10:LCD_Clear(BROWN);break;
								case 11:LCD_Clear(WHITE);break;
							}      					 
							i++;
							LED0=!LED0;	 
							delay_ms(1000);
							if(i==12)
							 { 
							    i=0;
								  LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
									LCD_DisplayString(20,40,16,"Author:Clever");
									LCD_DisplayString(30,80,24,"4.TFTLCD TEST");
									LCD_DisplayString(50,110,16,"KEY0:Screen Test");	
									LCD_DisplayString(50,130,16,"KEY1:Number Test");	
							 }		
					}							
			}

		if(keydown_data==KEY1_DATA)
		  {
			   LCD_Clear(WHITE);				
				 LCD_DisplayString(20,20,24,"Number Test");		
				 num=8357;
				 LCD_DisplayNum(40,60,num,6,24,0);
				 LCD_DisplayNum(40,90,num,6,24,1);
			}
	  delay_ms(5);	
	}
}

