#include "I2C.h"
 
 /****************************************************************************
* 名    称: void I2C_Init(void)
* 功    能：初始化I2C----初始化GPIO
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
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
* 名    称: void I2C_Start(void)
* 功    能：起始信号
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void I2C_Start(void)
{
    I2C_SDA(1);
	I2C_SCL(1);
	I2C_SDA(0);
	I2C_SCL(0);
}

 /****************************************************************************
* 名    称: void I2C_Stop(void)
* 功    能：停止信号
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void I2C_Stop(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SDA(1);
}

 /****************************************************************************
* 名    称: uint8_t I2C_Wait_Ack(void)
* 功    能：等待应答信号
* 入口参数：无
* 返回参数：1:接收应答失败  0:接收应答成�
* 说    明：无
* 作    者：liuli
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
* 名    称: void I2C_Send_Ack(void)
* 功    能：发送应答信号
* 入口参数：无
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void I2C_Send_Ack(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SCL(0);
	I2C_SDA(1);
}

/****************************************************************************
* 名    称: void I2C_Send_Byte(uint8_t data)
* 功    能：发送1个bit的数据
* 入口参数：data  --- 发送的数据
* 返回参数：无
* 说    明：无
* 作    者：liuli
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
* 名    称: uint8_t I2C_Read_Byte(void)
* 功    能：读取1个bit的数据
* 入口参数：
* 返回参数：uint8_t --- 返回1个bit数据
* 说    明：无
* 作    者：liuli
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