#include "KEY.h"
#include "LED.h"

/****************************************************************************
* 名    称: void KEY_Init(void)
* 功    能：初始化按键----初始化GPIO
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Init_Struct;
    KEY_GPIO_CLK_ENABLE();

    GPIO_Init_Struct.Pin  =  KEY0_GPIO_PIN|KEY1_GPIO_PIN|KEY2_GPIO_PIN;
    GPIO_Init_Struct.Mode =  GPIO_MODE_INPUT;
    GPIO_Init_Struct.Pull =  GPIO_PULLUP;
    GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(KEY1_GPIO_PORT,&GPIO_Init_Struct);

}

/****************************************************************************
* 名    称: uint8_t KEY_Scan(uint8_t mode)
* 功    能：按键输入识别
* 入口参数：mode 	--- 两种模式：1、连续输入  2、一次输入
* 返回参数：uint8_t --- 按键值
* 说    明：无
* 作    者：liuli
****************************************************************************/

uint8_t KEY_Scan(uint8_t mode)
{
    uint8_t Key_num;
    if(mode == 1)
    {
        HAL_Delay(20);
        if(KEY0_READ() == 0)  Key_num = KEY0_VALUE;
        if(KEY1_READ() == 0)  Key_num = KEY1_VALUE;
        if(KEY2_READ() == 0)  Key_num = KEY2_VALUE;

    }
    else
    {
        if(KEY0_READ() == 0)
        {
            HAL_Delay(20);
            while(KEY0_READ() == 0);
            HAL_Delay(20);
            Key_num = KEY0_VALUE;
        }
        if(KEY1_READ() == 0)
        {
            HAL_Delay(20);
            while(KEY1_READ() == 0);
            HAL_Delay(20);
            Key_num = KEY1_VALUE;
        }
        if(KEY2_READ() == 0)
        {
            HAL_Delay(20);
            while(KEY2_READ() == 0);
            HAL_Delay(20);
            Key_num = KEY2_VALUE;
        }
    }

    return Key_num;
}

/****************************************************************************
* 名    称: void KEY_test(void)
* 功    能：按键功能测试
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void KEY_test(void)
{
    if(KEY_Scan(0) == KEY0_VALUE)
    {
        LED0_Out(0);
    }
    if(KEY_Scan(0) == KEY1_VALUE)
    {
        LED1_Out(0);
    }
    if(KEY_Scan(0) == KEY2_VALUE)
    {
        LED0_Out(0);
        LED1_Out(1);
    }
}

/****************************************************************************
* 名    称: void KEY_FreeRTOS_test(void)
* 功    能：按键功能测试
* 入口参数：无
* 返回参数：无
* 说    明：用于FreeRTOS中
* 作    者：liuli
****************************************************************************/

void KEY_FreeRTOS_test(void)
{
	LED_Init();
	KEY_Init();
    while(1)
    {
        if(KEY_Scan(0) == KEY0_VALUE)
        {
            LED0_Out(0);
        }
        if(KEY_Scan(0) == KEY1_VALUE)
        {
            LED1_Out(0);
        }
        if(KEY_Scan(0) == KEY2_VALUE)
        {
            LED0_Out(0);
            LED1_Out(1);
        }
    }
}
