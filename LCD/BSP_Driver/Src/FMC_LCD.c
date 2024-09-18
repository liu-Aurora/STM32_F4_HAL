#include "FMC_LCD.h"
#include "Delay.h"

SRAM_HandleTypeDef LCDSRAM_Handler;    //SRAM句柄(用于控制LCD)

LCD_HandleTypeDef LCD_Handeler;		   // LCD常用变量

//初始化LCD的画笔颜色和背景色
uint16_t BRUSH_COLOR=BLACK;	//画笔颜色
uint16_t BACK_COLOR=WHITE;   //背景色

void LCD_FSMC_Config()
{
    //FMC选择的异步通信时序，这里参数调整时序，完成同步
    FSMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
    FSMC_NORSRAM_TimingTypeDef FSMC_WriteTim;

    LCDSRAM_Handler.Instance=FSMC_NORSRAM_DEVICE;
    LCDSRAM_Handler.Extended=FSMC_NORSRAM_EXTENDED_DEVICE;

    LCDSRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     					//使用NE4
    LCDSRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 		//地址/数据线不复用
    LCDSRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				//SRAM
    LCDSRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16位数据宽度
    LCDSRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE;	//是否使能突发访问,仅对同步突发存储器有效,此处未用到
    LCDSRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;  //等待信号的极性,仅在突发模式访问下有用
    LCDSRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT
    LCDSRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//存储器写使能
    LCDSRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;          		//等待使能位,此处未用到
    LCDSRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_ENABLE;        	//读写使用不同的时序
    LCDSRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//是否使能同步传输模式下的等待信号,此处未用到
    LCDSRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	//禁止突发写
    LCDSRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;

    //FMC读时序控制寄存器
    FSMC_ReadWriteTim.AddressSetupTime=0x0F;   //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns
    FSMC_ReadWriteTim.AddressHoldTime=0;
    FSMC_ReadWriteTim.DataSetupTime=60;				//数据保存时间为60个HCLK	=6*60=360ns
    FSMC_ReadWriteTim.AccessMode=FSMC_ACCESS_MODE_A;//模式A
    //FMC写时序控制寄存器
    FSMC_WriteTim.BusTurnAroundDuration=0;			//总线周转阶段持续时间为0，此变量不赋值的话会莫名其妙的自动修改为4。导致程序运行正常
    FSMC_WriteTim.AddressSetupTime=9;          		//地址建立时间（ADDSET）为9个HCLK =54ns
    FSMC_WriteTim.AddressHoldTime=0;
    FSMC_WriteTim.DataSetupTime=8;              	//数据保存时间为6ns*9个HCLK=54n
    FSMC_WriteTim.AccessMode=FSMC_ACCESS_MODE_A;    //模式A
    HAL_SRAM_Init(&LCDSRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);

    HAL_Delay(50);

}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_FSMC_CLK_ENABLE();			//使能FSMC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();			//使能GPIOD时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();			//使能GPIOE时钟
    __HAL_RCC_GPIOF_CLK_ENABLE();			//使能GPIOF时钟
    __HAL_RCC_GPIOG_CLK_ENABLE();			//使能GPIOG时钟

    //初始化PD0,1,4,5,8,9,10,14,15
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|
                     GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		//推挽复用
    GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;		//高速
    GPIO_Initure.Alternate=GPIO_AF12_FSMC;	//复用为FSMC
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //初始化

    //初始化PE7,8,9,10,11,12,13,14,15
    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|\
                     GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);

    //初始化PG2
    GPIO_Initure.Pin=GPIO_PIN_2;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);

    //初始化PG12
    GPIO_Initure.Pin=GPIO_PIN_12;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_Value)
{
    LCD_CMD = LCD_Reg;	   //写入要写的寄存器序号
    LCD_DATA = LCD_Value;  //向寄存器写入的数据
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_CMD=LCD_Reg;		//写入要读的寄存器序号
    delay_us(4);
    return LCD_DATA;		//返回读到的值
}

//lcd延时函数
void lcdm_delay(uint8_t i)
{
    while(i--);
}

//LCD开启显示
void LCD_DisplayOn(void)
{
    LCD_CMD=0x29;   //9341与1963开显示命令一样
}

//LCD关闭显示
void LCD_DisplayOff(void)
{
    LCD_CMD=0x28;   //9341与1963关显示命令一样
}

//开始写GRAM
void LCD_WriteGRAM(void)
{
    LCD_CMD=LCD_Handeler.write_gramcmd;
}

/****************************************************************************
* 名    称: void LCD_Open_Window(uint16_t X0,uint16_t Y0,uint16_t width,uint16_t height)
* 功    能：开窗口,并设置画点坐标到窗口左上角(X0,Y0)
* 入口参数：X0,Y0:窗口起始坐标(左上角)
            width,height:窗口宽度和高度
* 返回参数：无
* 说    明：窗体大小:width*height.
****************************************************************************/
void LCD_Open_Window(uint16_t X0,uint16_t Y0,uint16_t width,uint16_t height)
{
    //坐标从0开始,结尾坐标-1
    width=X0+width-1;    //算出右下角坐标
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
* 名    称: void Set_Scan_Direction(u8 direction)
* 功    能：设置LCD的扫描方向
* 入口参数：direction：扫描方向
* 返回参数：无
* 说    明：
****************************************************************************/
void Set_Scan_Direction(uint8_t direction)
{
    uint16_t skhda=0;
    uint16_t diomf=0;

    switch(direction)
    {
    case L2R_U2D:   //从左到右,从上到下
        skhda|=(0<<7)|(0<<6)|(0<<5);
        break;
    case L2R_D2U:   //从左到右,从下到上
        skhda|=(1<<7)|(0<<6)|(0<<5);
        break;
    case R2L_U2D:   //从右到左,从上到下
        skhda|=(0<<7)|(1<<6)|(0<<5);
        break;
    case R2L_D2U:   //从右到左,从下到上
        skhda|=(1<<7)|(1<<6)|(0<<5);
        break;
    case U2D_L2R:   //从上到下,从左到右
        skhda|=(0<<7)|(0<<6)|(1<<5);
        break;
    case U2D_R2L:   //从上到下,从右到左
        skhda|=(0<<7)|(1<<6)|(1<<5);
        break;
    case D2U_L2R:   //从下到上,从左到右
        skhda|=(1<<7)|(0<<6)|(1<<5);
        break;
    case D2U_R2L:   //从下到上,从右到左
        skhda|=(1<<7)|(1<<6)|(1<<5);
        break;
    }
    diomf=0X36;
    if(LCD_Handeler.lcd_id==0X9341)
        skhda|=0X08;
    LCD_WriteReg(diomf,skhda);
    LCD_Open_Window(0,0,LCD_Handeler.lcd_width,LCD_Handeler.lcd_height);  //设置完扫描方向后，开显示区域为全屏窗口
}

/****************************************************************************
* 名    称: void Set_Display_Mode(void)
* 功    能：设置LCD显示方向
* 入口参数：mode: 0,竖屏
                  1,横屏
* 返回参数：无
* 说    明：
****************************************************************************/
void Set_Display_Mode(void)
{
    LCD_Handeler.write_gramcmd=0X2C;
    LCD_Handeler.setxcmd=0X2A;
    LCD_Handeler.setycmd=0X2B;
    LCD_Handeler.lcd_width=240;
    LCD_Handeler.lcd_height=320;

    Set_Scan_Direction(L2R_U2D);	//设置扫描方向   从左到右,从下到上
}

/****************************************************************************
* 名    称: void LCD_SetCursor(u16 Xaddr, u16 Yaddr)
* 功    能：设置光标位置
* 入口参数：x：x坐标
            y：y坐标
* 返回参数：无
* 说    明：
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
* 名    称: uint16_t LCD_GetPoint(uint16_t x,uint16_t y)
* 功    能：读取某点的颜色值
* 入口参数：x：x坐标
            y：y坐标
* 返回参数：此点的颜色
* 说    明：
****************************************************************************/
uint16_t LCD_GetPoint(uint16_t x,uint16_t y)
{
    volatile uint16_t r=0,g=0,b=0;

    LCD_SetCursor(x,y);

    LCD_CMD=0X2E;   //9341与1963读GRAM指令一样
    r=LCD_DATA;

    lcdm_delay(2);
    b=LCD_DATA;    //9341要读2次
    g=r&0XFF;		  //9341第一次读取的是RG的值,R在前,G在后,各占8位
    g<<=8;

    return (((r>>11)<<11)|((g>>10)<<5)|(b>>11)); //9341需公式转换
}

/****************************************************************************
* 名    称: void LCD_DrawPoint(uint16_t x,uint16_t y)
* 功    能：画点（在该点写入画笔的颜色）
* 入口参数：x：x坐标
            y：y坐标
* 返回参数：无
* 说    明RUSH_COLOR:此点的颜色值
****************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
    LCD_SetCursor(x,y);		    //设置光标位置
    LCD_WriteGRAM();	        //开始写入GRAM
    LCD_DATA=BRUSH_COLOR;
}

/****************************************************************************
* 名    称: void LCD_Color_DrawPoint(u16 x,u16 y,u16 color)
* 功    能：在设置的坐标处画相应颜色（在该点写入自定义颜色）
* 入口参数：x：x坐标
            y：y坐标
            color 此点的颜色值
* 返回参数：无
* 说    明：color:写入此点的颜色值   GUI调用该函数
****************************************************************************/
void LCD_Color_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_SetCursor(x,y);
    LCD_CMD=LCD_Handeler.write_gramcmd;
    LCD_DATA=color;
}

/****************************************************************************
* 名    称: void LCD_Clear(u16 color)
* 功    能：清屏函数
* 入口参数：color: 要清屏的填充色
* 返回参数：无
* 说    明：
****************************************************************************/
void LCD_Clear(uint16_t color)
{
    uint32_t i=0;
    uint32_t pointnum=0;

    pointnum=LCD_Handeler.lcd_width*LCD_Handeler.lcd_height; 	 //得到LCD总点数
    LCD_SetCursor(0x00,0x00);	       //设置光标位置
    LCD_WriteGRAM();     		 //开始写入GRAM
    for(i=0; i<pointnum; i++)
    {
        LCD_DATA=color;
    }
}

uint16_t ILI9341_Read_id(void)
{
    uint16_t id;

    LCD_CMD=0xD3;	//9341读ID命令
    id=LCD_DATA;
    id=LCD_DATA; 	//0x00
    id=LCD_DATA;   //0x93
    id<<=8;
    id|=LCD_DATA;  //0x41

    return id;
}

//初始化lcd
void LCD_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟

    GPIO_Initure.Pin=GPIO_PIN_10;          	//PF10,背光控制
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);

    LCD_FSMC_Config();  //配置好FSMC就可以驱动液晶屏

    LCD_Handeler.lcd_id=ILI9341_Read_id(); //先读看看所接屏幕是不是9341驱动

    if(LCD_Handeler.lcd_id==0X9341) //此驱动,设置写时序为最快
    {
        FSMC_Bank1E->BWTR[6]&=~(0XF<<0); 	//地址建立时间清零
        FSMC_Bank1E->BWTR[6]&=~(0XF<<8);    //数据保存时间清零
        FSMC_Bank1E->BWTR[6]|=3<<0;		    //地址建立时间为3个HCLK =18ns
        FSMC_Bank1E->BWTR[6]|=2<<8;    	    //数据保存时间为6ns*3个HCLK=18ns
    }

//    if(LCD_Handeler.lcd_id==0X9341)	//9341初始化
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

        LCD_BL_Out(1);	  //点亮背光
//    }

    Set_Display_Mode();		 //初始化为竖屏
    LCD_Clear(WHITE);        //清屏白色
}


