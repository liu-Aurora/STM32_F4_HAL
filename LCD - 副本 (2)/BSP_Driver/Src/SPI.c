#include "SPI.h"

uint8_t SPI_SwapByte(uint8_t byte)
{ 
	uint8_t i,Receive_Byte;
	for(i = 0; i<8; i++)
	{
		SPI_SCK_OUT(1);
		SPI_MOSI_OUT(byte&(0x80>>i));
		SPI_SCK_OUT(0);
		SPI_SCK_OUT(1);
		if(SPI_MISO_READ() == 1)
		{
			Receive_Byte = Receive_Byte|(0x80>>i);
		}
	    SPI_SCK_OUT(0);
	}
	return  Receive_Byte;
}

void SPI_WriteReg(uint8_t Reg , uint8_t Value)
{
	SPI_CS_OUT(0);
	SPI_SwapByte(Reg);
	SPI_SwapByte(Value);
	SPI_CS_OUT(1);
}

uint8_t SPI_ReadReg(uint8_t Reg)
{
	uint8_t Value;
	SPI_CS_OUT(0);
	SPI_SwapByte(Reg);
	Value = SPI_SwapByte(0x00);
	SPI_CS_OUT(1);
	return Value;
}

void SPI_WriteBuf(uint8_t Reg , uint8_t *Buf, uint8_t Len)
{
	uint8_t i;
	SPI_CS_OUT(0);
	SPI_SwapByte(Reg);
	for(i = 0; i<Len ; i++)
	{
		SPI_SwapByte(Buf[i]);
	}
	SPI_CS_OUT(1);
}

void SPI_ReadBuf(uint8_t Reg, uint8_t *Buf, uint8_t Len)
{
	uint8_t i;
	SPI_CS_OUT(0);
	SPI_SwapByte(Reg);
	for(i = 0; i<Len; i++)
	{
		Buf[i] = SPI_SwapByte(0x00);
	}
	SPI_CS_OUT(1);
}	
