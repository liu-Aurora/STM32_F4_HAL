#include "FMC_LCD.h"
#include "Delay.h"

SRAM_HandleTypeDef LCDSRAM_Handler;    //SRAM���(���ڿ���LCD)

LCD_HandleTypeDef LCD_Handeler;		   // LCD���ñ���

//��ʼ��LCD�Ļ�����ɫ�ͱ���ɫ
uint16_t BRUSH_COLOR=BLACK;	//������ɫ
uint16_t BACK_COLOR=WHITE;   //����ɫ

void LCD_FSMC_Config()
{
    //FMCѡ����첽ͨ��ʱ�������������ʱ�����ͬ��
    FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
    FSMC_NORSRAM_TimingTypeDef FSMC_WriteTim;

    LCDSRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;
    LCDSRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;

    LCDSRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     					//ʹ��NE4
    LCDSRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 		//��ַ/�����߲�����
    LCDSRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				//SRAM
    LCDSRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16λ���ݿ��
    LCDSRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE;	//�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
    LCDSRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;  //�ȴ��źŵļ���,����ͻ��ģʽ����������
    LCDSRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
    LCDSRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//�洢��дʹ��
    LCDSRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;          		//�ȴ�ʹ��λ,�˴�δ�õ�
    LCDSRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_ENABLE;        	//��дʹ�ò�ͬ��ʱ��
    LCDSRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
    LCDSRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	//��ֹͻ��д
    LCDSRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;

    //FMC��ʱ����ƼĴ���
    FSMC_ReadWriteTim.AddressSetupTime=0x0F;   //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns
    FSMC_ReadWriteTim.AddressHoldTime=0;
    FSMC_ReadWriteTim.DataSetupTime=60;				//���ݱ���ʱ��Ϊ60��HCLK	=6*60=360ns
    FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//ģʽA
    //FMCдʱ����ƼĴ���
    FSMC_WriteTim.BusTurnAroundDuration=0;			//������ת�׶γ���ʱ��Ϊ0���˱�������ֵ�Ļ���Ī��������Զ��޸�Ϊ4�����³�����������
    FSMC_WriteTim.AddressSetupTime=9;          		//��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns
    FSMC_WriteTim.AddressHoldTime=0;
    FSMC_WriteTim.DataSetupTime=8;              	//���ݱ���ʱ��Ϊ6ns*9��HCLK=54n
    FSMC_WriteTim.AccessMode=FSMC_ACCESS_MODE_A;    //ģʽA
    HAL_SRAM_Init(&LCDSRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);

    HAL_Delay(50);

}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_FSMC_CLK_ENABLE();			//ʹ��FSMCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE();			//ʹ��GPIODʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();			//ʹ��GPIOEʱ��
    __HAL_RCC_GPIOF_CLK_ENABLE();			//ʹ��GPIOFʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();			//ʹ��GPIOGʱ��

    //��ʼ��PD0,1,4,5,8,9,10,14,15
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|
                     GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		//���츴��
    GPIO_Initure.Pull=GPIO_PULLUP;			//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;		//����
    GPIO_Initure.Alternate=GPIO_AF12_FSMC;	//����ΪFSMC
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��

    //��ʼ��PE7,8,9,10,11,12,13,14,15
    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|\
                     GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);

    //��ʼ��PG2
    GPIO_Initure.Pin=GPIO_PIN_2;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);

    //��ʼ��PG12
    GPIO_Initure.Pin=GPIO_PIN_12;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_Value)
{
    LCD_CMD = LCD_Reg;	   //д��Ҫд�ļĴ������
    LCD_DATA = LCD_Value;  //��Ĵ���д�������
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_CMD=LCD_Reg;		//д��Ҫ���ļĴ������
    delay_us(4);
    return LCD_DATA;		//���ض�����ֵ
}

//lcd��ʱ����
void lcdm_delay(uint8_t i)
{
    while(i--);
}

//LCD������ʾ
void LCD_DisplayOn(void)
{
    LCD_CMD=0x29;   //9341��1963����ʾ����һ��
}

//LCD�ر���ʾ
void LCD_DisplayOff(void)
{
    LCD_CMD=0x28;   //9341��1963����ʾ����һ��
}

//��ʼдGRAM
void LCD_WriteGRAM(void)
{
    LCD_CMD=LCD_Handeler.write_gramcmd;
}

/****************************************************************************
* ��    ��: void LCD_Open_Window(uint16_t X0,uint16_t Y0,uint16_t width,uint16_t height)
* ��    �ܣ�������,�����û������굽�������Ͻ�(X0,Y0)
* ��ڲ�����X0,Y0:������ʼ����(���Ͻ�)
            width,height:���ڿ�Ⱥ͸߶�
* ���ز�������
* ˵    ���������С:width*height.�B
****************************************************************************/
void LCD_Open_Window(uint16_t X0,uint16_t Y0,uint16_t width,uint16_t height)
{
    //�����0��ʼ,��β����-1
    width=X0+width-1;    //������½�����
    height=Y0+height-1;

    LCD_CMD=LCD_Handeler.setxcmd;
    LCD_DATA=X0>>8;
    LCD_DATA=X0&0XFF;
    LCD_DATA=width>>8;
    LCD_DATA=width&0XFF;
    LCD_CMD=LCD_Handeler.setycmd;
    LCD_DATA=Y0>>8;
    LCD_DATA=Y0&0XFF;
    LCD_DATA=height>>8;
    LCD_DATA=height&0XFF;
}

/****************************************************************************
* ��    ��: void Set_Scan_Direction(u8 direction)
* ��    �ܣ�����LCD��ɨ�跽��
* ��ڲ�����direction��ɨ�跽��
* ���ز�������
* ˵    ����
****************************************************************************/
void Set_Scan_Direction(uint8_t direction)
{
    uint16_t skhda=0;
    uint16_t diomf=0;

    switch(direction)
    {
    case L2R_U2D:   //������,���ϵ���
        skhda|=(0<<7)|(0<<6)|(0<<5);
        break;
    case L2R_D2U:   //������,���µ���
        skhda|=(1<<7)|(0<<6)|(0<<5);
        break;
    case R2L_U2D:   //���ҵ���,���ϵ���
        skhda|=(0<<7)|(1<<6)|(0<<5);
        break;
    case R2L_D2U:   //���ҵ���,���µ���
        skhda|=(1<<7)|(1<<6)|(0<<5);
        break;
    case U2D_L2R:   //���ϵ���,������
        skhda|=(0<<7)|(0<<6)|(1<<5);
        break;
    case U2D_R2L:   //���ϵ���,���ҵ���
        skhda|=(0<<7)|(1<<6)|(1<<5);
        break;
    case D2U_L2R:   //���µ���,������
        skhda|=(1<<7)|(0<<6)|(1<<5);
        break;
    case D2U_R2L:   //���µ���,���ҵ���
        skhda|=(1<<7)|(1<<6)|(1<<5);
        break;
    }
    diomf=0X36;
    if(LCD_Handeler.lcd_id==0X9341)
        skhda|=0X08;
    LCD_WriteReg(diomf,skhda);
    LCD_Open_Window(0,0,LCD_Handeler.lcd_width,LCD_Handeler.lcd_height);  //������ɨ�跽��󣬿���ʾ����Ϊȫ������
}

/****************************************************************************
* ��    ��: void Set_Display_Mode(void)
* ��    �ܣ�����LCD��ʾ����
* ��ڲ�����mode: 0,����
                  1,����
* ���ز�������
* ˵    �����B
****************************************************************************/
void Set_Display_Mode(void)
{
    LCD_Handeler.write_gramcmd=0X2C;
    LCD_Handeler.setxcmd=0X2A;
    LCD_Handeler.setycmd=0X2B;
    LCD_Handeler.lcd_width=240;
    LCD_Handeler.lcd_height=320;

    Set_Scan_Direction(L2R_U2D);	//����ɨ�跽��   ������,���µ���
}

/****************************************************************************
* ��    ��: void LCD_SetCursor(u16 Xaddr, u16 Yaddr)
* ��    �ܣ����ù��λ��
* ��ڲ�����x��x����
            y��y����
* ���ز�������
* ˵    ����
****************************************************************************/
void LCD_SetCursor(uint16_t Xaddr, uint16_t Yaddr)
{

    LCD_CMD=LCD_Handeler.setxcmd;
    LCD_DATA=(Xaddr>>8);
    LCD_DATA=(Xaddr&0XFF);
    LCD_CMD=LCD_Handeler.setycmd;
    LCD_DATA=(Yaddr>>8);
    LCD_DATA=(Yaddr&0XFF);

}


/****************************************************************************
* ��    ��: uint16_t LCD_GetPoint(uint16_t x,uint16_t y)
* ��    �ܣ���ȡĳ�����ɫֵ
* ��ڲ�����x��x����
            y��y����
* ���ز������˵����ɫ
* ˵    ����
****************************************************************************/
uint16_t LCD_GetPoint(uint16_t x,uint16_t y)
{
    volatile uint16_t r=0,g=0,b=0;

    LCD_SetCursor(x,y);

    LCD_CMD=0X2E;   //9341��1963��GRAMָ��һ��
    r=LCD_DATA;

    lcdm_delay(2);
    b=LCD_DATA;    //9341Ҫ��2��
    g=r&0XFF;		  //9341��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
    g<<=8;

    return (((r>>11)<<11)|((g>>10)<<5)|(b>>11)); //9341�蹫ʽת��
}

/****************************************************************************
* ��    ��: void LCD_DrawPoint(uint16_t x,uint16_t y)
* ��    �ܣ����㣨�ڸõ�д�뻭�ʵ���ɫ��
* ��ڲ�����x��x����
            y��y����
* ���ز�������
* ˵    ���BRUSH_COLOR:�˵����ɫֵ
****************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
    LCD_SetCursor(x,y);		    //���ù��λ��
    LCD_WriteGRAM();	        //��ʼд��GRAM
    LCD_DATA=BRUSH_COLOR;
}

/****************************************************************************
* ��    ��: void LCD_Color_DrawPoint(u16 x,u16 y,u16 color)
* ��    �ܣ������õ����괦����Ӧ��ɫ���ڸõ�д���Զ�����ɫ��
* ��ڲ�����x��x����
            y��y����
            color �˵����ɫֵ
* ���ز�������
* ˵    ����color:д��˵����ɫֵ   GUI���øú���
****************************************************************************/
void LCD_Color_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_SetCursor(x,y);
    LCD_CMD=LCD_Handeler.write_gramcmd;
    LCD_DATA=color;
}

/****************************************************************************
* ��    ��: void LCD_Clear(u16 color)
* ��    �ܣ���������
* ��ڲ�����color: Ҫ���������ɫ
* ���ز�������
* ˵    �����B
****************************************************************************/
void LCD_Clear(uint16_t color)
{
    uint32_t i=0;
    uint32_t pointnum=0;

    pointnum=LCD_Handeler.lcd_width*LCD_Handeler.lcd_height; 	 //�õ�LCD�ܵ���
    LCD_SetCursor(0x00,0x00);	       //���ù��λ��
    LCD_WriteGRAM();     		 //��ʼд��GRAM
    for(i=0; i<pointnum; i++)
    {
        LCD_DATA=color;
    }
}

uint16_t ILI9341_Read_id(void)
{
    uint16_t id;

    LCD_CMD=0xD3;	//9341��ID����
    id=LCD_DATA;
    id=LCD_DATA; 	//0x00
    id=LCD_DATA;   //0x93
    id<<=8;
    id|=LCD_DATA;  //0x41

    return id;
}

//��ʼ��lcd
void LCD_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��

    GPIO_Initure.Pin=GPIO_PIN_10;          	//PF10,�������
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);

    LCD_FSMC_Config();  //���ú�FSMC�Ϳ�������Һ����

    LCD_Handeler.lcd_id=ILI9341_Read_id(); //�ȶ�����������Ļ�ǲ���9341����

    if(LCD_Handeler.lcd_id==0X9341) //������,����дʱ��Ϊ���
    {
        FSMC_Bank1E->BWTR[6]&=~(0XF<<0); 	//��ַ����ʱ������
        FSMC_Bank1E->BWTR[6]&=~(0XF<<8);    //���ݱ���ʱ������
        FSMC_Bank1E->BWTR[6]|=3<<0;		    //��ַ����ʱ��Ϊ3��HCLK =18ns
        FSMC_Bank1E->BWTR[6]|=2<<8;    	    //���ݱ���ʱ��Ϊ6ns*3��HCLK=18ns
    }

//    if(LCD_Handeler.lcd_id==0X9341)	//9341��ʼ��
//    {
        LCD_CMD=0xCF;
        LCD_DATA=0x00;
        LCD_DATA=0xC1;
        LCD_DATA=0X30;
        LCD_CMD=0xED;
        LCD_DATA=0x64;
        LCD_DATA=0x03;
        LCD_DATA=0X12;
        LCD_DATA=0X81;
        LCD_CMD=0xE8;
        LCD_DATA=0x85;
        LCD_DATA=0x10;
        LCD_DATA=0x7A;
        LCD_CMD=0xCB;
        LCD_DATA=0x39;
        LCD_DATA=0x2C;
        LCD_DATA=0x00;
        LCD_DATA=0x34;
        LCD_DATA=0x02;
        LCD_CMD=0xF7;
        LCD_DATA=0x20;
        LCD_CMD=0xEA;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_CMD=0xC0;
        LCD_DATA=0x1B;
        LCD_CMD=0xC1;
        LCD_DATA=0x01;
        LCD_CMD=0xC5;
        LCD_DATA=0x30;
        LCD_DATA=0x30;
        LCD_CMD=0xC7;
        LCD_DATA=0XB7;
        LCD_CMD=0x36;
        LCD_DATA=0x48;
        LCD_CMD=0x3A;
        LCD_DATA=0x55;
        LCD_CMD=0xB1;
        LCD_DATA=0x00;
        LCD_DATA=0x1A;
        LCD_CMD=0xB6;
        LCD_DATA=0x0A;
        LCD_DATA=0xA2;
        LCD_CMD=0xF2;
        LCD_DATA=0x00;
        LCD_CMD=0x26;
        LCD_DATA=0x01;
        LCD_CMD=0xE0;
        LCD_DATA=0x0F;
        LCD_DATA=0x2A;
        LCD_DATA=0x28;
        LCD_DATA=0x08;
        LCD_DATA=0x0E;
        LCD_DATA=0x08;
        LCD_DATA=0x54;
        LCD_DATA=0XA9;
        LCD_DATA=0x43;
        LCD_DATA=0x0A;
        LCD_DATA=0x0F;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_CMD=0XE1;
        LCD_DATA=0x00;
        LCD_DATA=0x15;
        LCD_DATA=0x17;
        LCD_DATA=0x07;
        LCD_DATA=0x11;
        LCD_DATA=0x06;
        LCD_DATA=0x2B;
        LCD_DATA=0x56;
        LCD_DATA=0x3C;
        LCD_DATA=0x05;
        LCD_DATA=0x10;
        LCD_DATA=0x0F;
        LCD_DATA=0x3F;
        LCD_DATA=0x3F;
        LCD_DATA=0x0F;
        LCD_CMD=0x2B;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_DATA=0x01;
        LCD_DATA=0x3f;
        LCD_CMD=0x2A;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_DATA=0x00;
        LCD_DATA=0xef;
        LCD_CMD=0x11;
        delay_ms(120);
        LCD_CMD=0x29;

        LCD_BL_Out(1);	  //��������
//    }

    Set_Display_Mode();		 //��ʼ��Ϊ����
    LCD_Clear(WHITE);        //������ɫ
}


