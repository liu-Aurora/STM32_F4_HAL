#include "AT24C02.h"
#include "I2C.h"

/****************************************************************************
* 名    称: void AT24C02_Init(void)
* 功    能：初始化AT24C02的I2C引脚
* 入口参数：无
* 返回参数：无
* 说    明：可用I2C.C文件中初始化，但修改引脚
* 作    者：liuli
****************************************************************************/

void AT24C02_Init(void)
{			
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();   
	
	GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;  
	GPIO_Initure.Pull=GPIO_PULLUP;          
	GPIO_Initure.Speed=GPIO_SPEED_FAST;     
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    I2C_Stop();   
}

/****************************************************************************
* 名    称: void AT24C02_WriteByte(uint8_t Write_address,uint8_t Data)
* 功    能：向AT24C02中指定地址，写入一个bit数据
* 入口参数：Write_address  --- 写地址
			Data           --- 写内容
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void AT24C02_WriteByte(uint8_t Write_address,uint8_t Data)
{
	I2C_Start();
	I2C_Send_Byte(0xA0);
	I2C_Wait_Ack();
	I2C_Send_Byte(Write_address);
	I2C_Wait_Ack();
	I2C_Send_Byte(Data);
	I2C_Wait_Ack();
	I2C_Stop();
	HAL_Delay(10);
}

/****************************************************************************
* 名    称: uint8_t AT24C02_ReadByte(uint8_t Read_address)
* 功    能：向AT24C02中指定地址，读取一个bit的数据
* 入口参数：无
* 返回参数：uint8_t  --- 还会读取数据
* 说    明：无
* 作    者：liuli
****************************************************************************/

uint8_t AT24C02_ReadByte(uint8_t Read_address)
{
	uint8_t data;
	
	I2C_Start();
    I2C_Send_Byte(0xA0);
	I2C_Wait_Ack();
	I2C_Send_Byte(Read_address);
	I2C_Wait_Ack();
	I2C_Start();
	I2C_Send_Byte(0xA1);
	I2C_Wait_Ack();
	data = I2C_Read_Byte();
	I2C_Send_Ack();
	I2C_Stop();
	
	return data; 
}

/****************************************************************************
* 名    称: void AT24C02_Read_Continuity(uint8_t ReadAddress,uint8_t* pBuffer,uint8_t ReadNum)
* 功    能：向AT24C02中指定地址，连续读取一个bit的数据
* 入口参数：ReadAddress :开始读出的地址  0~255
            pBuffer  :数据数组首地址
            ReadNum:要读出数据的个数
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void AT24C02_Read_Continuity(uint8_t ReadAddress,uint8_t* pBuffer,uint8_t ReadNum)
{
	while(ReadNum--)
	{
		*pBuffer = AT24C02_ReadByte(ReadAddress);
		ReadAddress++;
		pBuffer++;
	}	
}

/****************************************************************************
* 名    称: void AT24C02_Write_Continuity(uint8_t WriteAddress,uint8_t* pBuffer,uint8_t WriteNum)
* 功    能：向AT24C02中指定地址，连续写入一个bit的数据
* 入口参数：WriteAddress :开始写入的地址  0~255
            pBuffer  :数据数组首地址
            WriteNum:要写入数据的个数
* 返回参数：无
* 说    明：无
* 作    者：liuli
****************************************************************************/

void AT24C02_Write_Continuity(uint8_t WriteAddress,uint8_t* pBuffer,uint8_t WriteNum)
{
	while(WriteNum--)
	{
		AT24C02_WriteByte(WriteAddress,*pBuffer);
		WriteAddress++;
		pBuffer++;
	}	
}



void ATC24C02_Test(void)
{
	AT24C02_Init();

}
