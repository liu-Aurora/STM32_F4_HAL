#ifndef _AT24C02_H_
#define _AT24C02_H_

#include "stm32f4xx_hal.h"

void AT24C02_Init(void);
void AT24C02_WriteByte(uint8_t Write_address,uint8_t Data);
uint8_t AT24C02_ReadByte(uint8_t Read_address);
void AT24C02_Read_Continuity(uint8_t ReadAddress,uint8_t* pBuffer,uint8_t ReadNum);
void AT24C02_Write_Continuity(uint8_t WriteAddress,uint8_t* pBuffer,uint8_t WriteNum);
void ATC24C02_Test(void);	


#endif



