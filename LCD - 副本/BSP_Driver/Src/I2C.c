#include "I2C.h"
 
 /****************************************************************************
* Ãû    ³Æ: void I2C_Init(void)
* ¹¦    ÄÜ£º³õÊ¼»¯I2C----³õÊ¼»¯GPIO
* Èë¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
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
* Ãû    ³Æ: void I2C_Start(void)
* ¹¦    ÄÜ£ºÆðÊ¼ÐÅºÅ
* Èë¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
****************************************************************************/

void I2C_Start(void)
{
    I2C_SDA(1);
	I2C_SCL(1);
	I2C_SDA(0);
	I2C_SCL(0);
}

 /****************************************************************************
* Ãû    ³Æ: void I2C_Stop(void)
* ¹¦    ÄÜ£ºÍ£Ö¹ÐÅºÅ
* Èë¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
****************************************************************************/

void I2C_Stop(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SDA(1);
}

 /****************************************************************************
* Ãû    ³Æ: uint8_t I2C_Wait_Ack(void)
* ¹¦    ÄÜ£ºµÈ´ýÓ¦´ðÐÅºÅ
* Èë¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£º1:½ÓÊÕÓ¦´ðÊ§°Ü  0:½ÓÊÕÓ¦´ð³É¹
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
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
* Ãû    ³Æ: void I2C_Send_Ack(void)
* ¹¦    ÄÜ£º·¢ËÍÓ¦´ðÐÅºÅ
* Èë¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
****************************************************************************/

void I2C_Send_Ack(void)
{
	I2C_SDA(0);
	I2C_SCL(1);
	I2C_SCL(0);
	I2C_SDA(1);
}

/****************************************************************************
* Ãû    ³Æ: void I2C_Send_Byte(uint8_t data)
* ¹¦    ÄÜ£º·¢ËÍ1¸öbitµÄÊý¾Ý
* Èë¿Ú²ÎÊý£ºdata  --- ·¢ËÍµÄÊý¾Ý
* ·µ»Ø²ÎÊý£ºÎÞ
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
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
* Ãû    ³Æ: uint8_t I2C_Read_Byte(void)
* ¹¦    ÄÜ£º¶ÁÈ¡1¸öbitµÄÊý¾Ý
* Èë¿Ú²ÎÊý£º
* ·µ»Ø²ÎÊý£ºuint8_t --- ·µ»Ø1¸öbitÊý¾Ý
* Ëµ    Ã÷£ºÎÞ
* ×÷    Õß£ºliuli
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