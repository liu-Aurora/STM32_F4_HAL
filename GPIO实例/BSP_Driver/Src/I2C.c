#include "I2C.h"
 
 /****************************************************************************
* ��    ��: void I2C_Init(void)
* ��    �ܣ���ʼ��I2C----��ʼ��GPIO
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	I2C_SDA_GPIO_CLE_ENABLE();
	I2C_SCL_GPIO_CLE_ENABLE();
	
	GPIO_InitStruct.Pin = I2C_SCL_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(I2C_SCL_GPIO_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = I2C_SDA_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(I2C_SDA_GPIO_PORT,&GPIO_InitStruct);
	
	I2C_SDA(1);
	I2C_SCL(1);
}

 /****************************************************************************
* ��    ��: void I2C_Start(void)
* ��    �ܣ���ʼ�ź�
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void I2C_Start(void)
{
    I2C_SDA(1);
	I2C_SCL(1);
	I2C_SDA(0);
	I2C_SCL(0);
}

 /****************************************************************************
* ��    ��: void I2C_Stop(void)
* ��    �ܣ�ֹͣ�ź�
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void I2C_Stop(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SDA(1);
}

 /****************************************************************************
* ��    ��: uint8_t I2C_Wait_Ack(void)
* ��    �ܣ��ȴ�Ӧ���ź�
* ��ڲ�������
* ���ز�����1:����Ӧ��ʧ��  0:����Ӧ��ɹ
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

uint8_t I2C_Wait_Ack(void)
{
	uint8_t Ack;
	I2C_SDA(1);
	I2C_SCL(1);
	if(I2C_READ())
	{
		Ack = 1;
	}
	else
	{
		Ack = 0;
	}
	I2C_SCL(0);
	return Ack;
}

/****************************************************************************
* ��    ��: void I2C_Send_Ack(void)
* ��    �ܣ�����Ӧ���ź�
* ��ڲ�������
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void I2C_Send_Ack(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SCL(0);
	I2C_SDA(1);
}

/****************************************************************************
* ��    ��: void I2C_Send_Byte(uint8_t data)
* ��    �ܣ�����1��bit������
* ��ڲ�����data  --- ���͵�����
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

void I2C_Send_Byte(uint8_t data)
{
	uint8_t i;
	
	for(i = 0; i<8; i++)
	{
		I2C_SDA(data&(0x80>>i));
		I2C_SCL(1);
		I2C_SDA(0);
	}
	I2C_Wait_Ack();
}	

/****************************************************************************
* ��    ��: uint8_t I2C_Read_Byte(void)
* ��    �ܣ���ȡ1��bit������
* ��ڲ�����
* ���ز�����uint8_t --- ����1��bit����
* ˵    ������
* ��    �ߣ�liuli
****************************************************************************/

uint8_t I2C_Read_Byte(void)
{
	uint8_t data;
	uint8_t i;
	
	I2C_SDA(1);
	for(i = 0; i<8; i++)
	{
		I2C_SCL(1);
		if(I2C_READ())
		{
			data = (data<<1)|(0x01);
		}
		else
		{
			data =  data<<i;
		}
		I2C_SCL(0);
	}
	
	I2C_Send_Ack();
	return data;
}