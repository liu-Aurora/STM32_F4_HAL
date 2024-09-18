#include "LED.h"

/****************************************************************************
* ��    ��: void LED_Init(void)
* ��    �ܣ���ʼ��LED----��ʼ��GPIO
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	LED0_GPIO_CLK_ENABLE();
	LED1_GPIO_CLK_ENABLE();
	LED2_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = LED0_GPIO_PIN|LED1_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(LED0_GPIO_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.Pin =  LED2_GPIO_PIN;
	HAL_GPIO_Init(LED2_GPIO_PORT,&GPIO_InitStruct);
	
	LED0_Out(1);
	LED1_Out(1);
	LED2_Out(1);
}

/****************************************************************************
* ��    ��: void LED_test(void)
* ��    �ܣ�����LED�Ĺ���
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void LED_test(void)
{
	LED_Init();

	LED0_Out(0);
	HAL_Delay(1000);
	LED0_Out(1);
	
	LED1_Out(0);
	HAL_Delay(1000);
	LED1_Out(1);
	
	LED2_Out(0);
	HAL_Delay(1000);
	LED2_Out(1);		
}

/****************************************************************************
* ��    ��: void LED_FreeRTOS_test(void)
* ��    �ܣ�����LED�Ĺ���
* ��ڲ�������
* ���ز�������
* ˵    ������FreeRTOS��
* ��    �ߣ�liuli
****************************************************************************/

void LED_FreeRTOS_test(void)
{
	LED_Init();

	LED0_Out(0);
	HAL_Delay(1000);
	LED0_Out(1);
	
	LED1_Out(0);
	HAL_Delay(1000);
	LED1_Out(1);
	
	LED2_Out(0);
	HAL_Delay(1000);
	LED2_Out(1);		
}