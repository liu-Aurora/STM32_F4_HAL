#include "LED.h"

/****************************************************************************
* 名    称: void LED_Init(void)
* 功    能：初始化LED----初始化GPIO
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
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
* 名    称: void LED_test(void)
* 功    能：测试LED的功能
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
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
* 名    称: void LED_FreeRTOS_test(void)
* 功    能：测试LED的功能
* 入口参数：无
* 返回参数：无
* 说    明：用FreeRTOS中
* 作    者：liuli
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