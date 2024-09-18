#include "AT24C02.h"
#include "I2C.h"

/****************************************************************************
* ��    ��: void AT24C02_Init(void)
* ��    �ܣ���ʼ��AT24C02��I2C����
* ��ڲ�������
* ���ز�������
* ˵    ��������I2C.C�ļ��г�ʼ�������޸�����
* ��    �ߣ�liuli
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
* ��    ��: void AT24C02_WriteByte(uint8_t Write_address,uint8_t Data)
* ��    �ܣ���AT24C02��ָ����ַ��д��һ��bit����
* ��ڲ�����Write_address  --- д��ַ
			Data           --- д����
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: uint8_t AT24C02_ReadByte(uint8_t Read_address)
* ��    �ܣ���AT24C02��ָ����ַ����ȡһ��bit������
* ��ڲ�������
* ���ز�����uint8_t  --- �����ȡ����
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: void AT24C02_Read_Continuity(uint8_t ReadAddress,uint8_t* pBuffer,uint8_t ReadNum)
* ��    �ܣ���AT24C02��ָ����ַ��������ȡһ��bit������
* ��ڲ�����ReadAddress :��ʼ�����ĵ�ַ  0~255
            pBuffer  :���������׵�ַ
            ReadNum:Ҫ�������ݵĸ���
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
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
* ��    ��: void AT24C02_Write_Continuity(uint8_t WriteAddress,uint8_t* pBuffer,uint8_t WriteNum)
* ��    �ܣ���AT24C02��ָ����ַ������д��һ��bit������
* ��ڲ�����WriteAddress :��ʼд��ĵ�ַ  0~255
            pBuffer  :���������׵�ַ
            WriteNum:Ҫд�����ݵĸ���
* ���ز�������
* ˵    ������
* ��    �ߣ�liuli
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
