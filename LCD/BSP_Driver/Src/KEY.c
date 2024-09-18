#include "KEY.h"
#include "LED.h"

/****************************************************************************
* ��    ��: void KEY_Init(void)
* ��    �ܣ���ʼ������----��ʼ��GPIO
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: uint8_t KEY_Scan(uint8_t mode)
* ��    �ܣ���������ʶ��
* ��ڲ�����mode 	--- ����ģʽ��1����������  2��һ������
* ���ز�����uint8_t --- ����ֵ
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: void KEY_test(void)
* ��    �ܣ��������ܲ���
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: void KEY_FreeRTOS_test(void)
* ��    �ܣ��������ܲ���
* ��ڲ�������
* ���ز�������
* ˵    ��������FreeRTOS��
* ��    �ߣ�liuli
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
