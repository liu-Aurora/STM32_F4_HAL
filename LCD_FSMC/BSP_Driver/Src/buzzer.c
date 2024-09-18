#include "buzzer.h"
#include "LED.h"

/****************************************************************************
* 名    称: void Buzzer_Init(void)
* 功    能：初始化Buzzer----初始化GPIO
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	BUZZER_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BUZZER_GPIO_PIN;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP ;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(BUZZER_GPIO_PORT,&GPIO_InitStruct);
	BUZZER_Out(0);
}


/****************************************************************************
* 名    称: void Buzzer_test(void)
* 功    能：测试Buzzer的功能
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void Buzzer_test(void)
{
	BUZZER_Out(1);
	LED0_Out(0);
	HAL_Delay(1000);
	
	BUZZER_Out(0);
	LED0_Out(1);
	HAL_Delay(5000);
}

/****************************************************************************
* 名    称: void Buzzer_FreeRTOS_test(void)
* 功    能：测试Buzzer的功能
* 入口参数：无
* 返回参数：无
* 说    明：用于freerots中
* 作    者：liuli
****************************************************************************/

void Buzzer_FreeRTOS_test(void)
{
	Buzzer_Init();
	LED_Init();
	while(1)
	{
	  BUZZER_Out(1);
	  LED0_Out(0);
	  HAL_Delay(1000);
		
	  BUZZER_Out(0);
	  LED0_Out(1);
	  HAL_Delay(5000);	
	}

}