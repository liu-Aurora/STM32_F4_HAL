//#include "LCD.h"
//#include "8080.h"

///* 管理LCD重要参数 */
//_lcd_dev lcddev;

///* LCD的画笔颜色和背景色 */
//uint32_t g_point_color = 0XF800;    	/* 画笔颜色 */
//uint32_t g_back_color  = 0XFFFF;    	/* 背景色 */

//void lcd_wr_data(uint16_t data)
//{
//    RS8080_Out(1);
//	CS8080_Out(0);
//	DATA8080_OUT(data);
//	WR8080_Out(0);
//	WR8080_Out(1);
//	CS8080_Out(1);
//}  

///* 8080 写命令 */
//void lcd_wr_regno(uint16_t command)
//{
//    RS8080_Out(0);
//	CS8080_Out(0);
//	DATA8080_OUT(command);
//	WR8080_Out(0);
//	WR8080_Out(1);
//	CS8080_Out(1);
//}

///* 往寄存器写值 */
//void lcd_write_reg(uint16_t regno, uint16_t data)
//{
//    WR_Reg_8008(regno);    /* 写入要写的寄存器序号 */
//    WR_Data_8080(data);      /* 写入数据 */
//}

//static void lcd_opt_delay(uint32_t i)
//{
//    while(i--);
//}

///* LCD读数据 */
//uint16_t lcd_rd_data(void)
//{
//    volatile uint16_t ram;  /* 防止被优化 */
//    
//    GPIO_InitTypeDef gpio_init_struct;
//    /* LCD_DATA 引脚模式设置, 上拉输入, 准备接收数据 */
//    gpio_init_struct.Pin = DATA8080_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_INPUT;
//    gpio_init_struct.Pull = GPIO_PULLUP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(DATA8080_GPIO_PORT, &gpio_init_struct); 

//	CS8080_Out(0);
//	RS8080_Out(1);
//	RD8080_Out(0);
//	lcd_opt_delay(2);
//	ram = LCD_DATA_IN();
//	RD8080_Out(1);
//	CS8080_Out(1);
//	
//     
//    /* LCD_DATA 引脚模式设置, 推挽输出, 恢复输出状态 */
//    gpio_init_struct.Pin = DATA8080_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
//    gpio_init_struct.Pull = GPIO_PULLUP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(DATA8080_GPIO_PORT, &gpio_init_struct);   

//    return ram;
//}

///* 准备写GRAM */
//void lcd_write_ram_prepare(void)
//{
//    WR_Reg_8008(lcddev.wramcmd);
//}

///* 设置坐标 */
//void lcd_set_cursor(uint16_t x, uint16_t y)
//{
//    lcd_wr_regno(lcddev.setxcmd);
//    lcd_wr_data(x >> 8);
//    lcd_wr_data(x & 0xFF);
//    lcd_wr_regno(lcddev.setycmd);
//    lcd_wr_data(y >> 8);
//    lcd_wr_data(y & 0xFF);
//}

///* 画点 */
//void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
//{
//    lcd_set_cursor(x, y);
//    lcd_write_ram_prepare();
//    lcd_wr_data(color);
//}

///* 读点 */
//uint16_t  lcd_read_point (uint16_t x, uint16_t y)
//{
//    uint16_t r = 0, g = 0, b = 0;   /* 定义变量 */
//    
//    lcd_set_cursor(x, y);           /* 设置坐标 */
//    lcd_wr_regno(0X2E);             /* 发读点命令 */
//    r = lcd_rd_data();              /* 假读 */
//    r = lcd_rd_data();              /* 读rg */
//    b = lcd_rd_data();              /* 读b */
//    g = r & 0XFF;                   /* 得到g值 */
//    return (((r >> 11) << 11) | ((g >> 2) << 5) | (b >> 11));
//}

//void lcd_ex_ili9341_reginit(void)
//{
//    lcd_wr_regno(0xCF);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0xC1);
//    lcd_wr_data(0X30);
//    lcd_wr_regno(0xED);
//    lcd_wr_data(0x64);
//    lcd_wr_data(0x03);
//    lcd_wr_data(0X12);
//    lcd_wr_data(0X81);
//    lcd_wr_regno(0xE8);
//    lcd_wr_data(0x85);
//    lcd_wr_data(0x10);
//    lcd_wr_data(0x7A);
//    lcd_wr_regno(0xCB);
//    lcd_wr_data(0x39);
//    lcd_wr_data(0x2C);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x34);
//    lcd_wr_data(0x02);
//    lcd_wr_regno(0xF7);
//    lcd_wr_data(0x20);
//    lcd_wr_regno(0xEA);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_regno(0xC0); /* Power control */
//    lcd_wr_data(0x1B);  /* VRH[5:0] */
//    lcd_wr_regno(0xC1); /* Power control */
//    lcd_wr_data(0x01);  /* SAP[2:0];BT[3:0] */
//    lcd_wr_regno(0xC5); /* VCM control */
//    lcd_wr_data(0x30);  /* 3F */
//    lcd_wr_data(0x30);  /* 3C */
//    lcd_wr_regno(0xC7); /* VCM control2 */
//    lcd_wr_data(0XB7);
//    lcd_wr_regno(0x36); /*  Memory Access Control */
//    lcd_wr_data(0x48);
//    lcd_wr_regno(0x3A);
//    lcd_wr_data(0x55);
//    lcd_wr_regno(0xB1);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x1A);
//    lcd_wr_regno(0xB6); /*  Display Function Control */
//    lcd_wr_data(0x0A);
//    lcd_wr_data(0xA2);
//    lcd_wr_regno(0xF2); /*  3Gamma Function Disable */
//    lcd_wr_data(0x00);
//    lcd_wr_regno(0x26); /* Gamma curve selected */
//    lcd_wr_data(0x01);
//    lcd_wr_regno(0xE0); /* Set Gamma */
//    lcd_wr_data(0x0F);
//    lcd_wr_data(0x2A);
//    lcd_wr_data(0x28);
//    lcd_wr_data(0x08);
//    lcd_wr_data(0x0E);
//    lcd_wr_data(0x08);
//    lcd_wr_data(0x54);
//    lcd_wr_data(0XA9);
//    lcd_wr_data(0x43);
//    lcd_wr_data(0x0A);
//    lcd_wr_data(0x0F);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_regno(0XE1);    /* Set Gamma */
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x15);
//    lcd_wr_data(0x17);
//    lcd_wr_data(0x07);
//    lcd_wr_data(0x11);
//    lcd_wr_data(0x06);
//    lcd_wr_data(0x2B);
//    lcd_wr_data(0x56);
//    lcd_wr_data(0x3C);
//    lcd_wr_data(0x05);
//    lcd_wr_data(0x10);
//    lcd_wr_data(0x0F);
//    lcd_wr_data(0x3F);
//    lcd_wr_data(0x3F);
//    lcd_wr_data(0x0F);
//    lcd_wr_regno(0x2B);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x01);
//    lcd_wr_data(0x3f);
//    lcd_wr_regno(0x2A);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0x00);
//    lcd_wr_data(0xef);
//    lcd_wr_regno(0x11); /* Exit Sleep */
//	HAL_Delay(120);
//    lcd_wr_regno(0x29); /* display on */
// }

// void lcd_clear(uint16_t color)
//{
//    uint32_t index = 0;
//    uint32_t totalpoint = lcddev.width;
//    
//    totalpoint *= lcddev.height;    /* 得到总点数 */
//    lcd_set_cursor(0, 0);   		/* 设置光标位置 */
//    lcd_write_ram_prepare();        /* 开始写入GRAM */

//    RS8080_Out(1);                      /* RS=1,表示写数据 */
//    CS8080_Out(0);
//    
//    for (index = 0; index < totalpoint; index++)
//    {
//        DATA8080_OUT(color);        /* 写入要写的数据 */
//        WR8080_Out(0);
//        WR8080_Out(1);
//    }
//    
//    CS8080_Out(1);
//}

// 
//void lcd_init(void)
//{
//    GPIO_InitTypeDef gpio_init_struct;
//    
//	CS8080_GPIO_CLK_ENABLE();    /* LCD_CS脚时钟使能 */
//	WR8080_GPIO_CLK_ENABLE();    /* LCD_WR脚时钟使能 */
//	RS8080_GPIO_CLK_ENABLE();    /* LCD_RS脚时钟使能 */
//	RD8080_GPIO_CLK_ENABLE();    /* LCD_RD脚时钟使能 */
//	LCD_BL_GPIO_CLK_ENABLE();	 /* LCD_BL脚时钟使能 */
//	DATA8080_GPIO__CLK_ENABLE(); /* LCD_DATA脚时钟使能 */
//	
//	gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽复用 */
//    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
//    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL引脚模式设置(推挽输出) */

//    gpio_init_struct.Pin = CS8080_GPIO_PIN;
//    HAL_GPIO_Init(CS8080_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_CS引脚 */

//    gpio_init_struct.Pin = WR8080_GPIO_PIN;
//    HAL_GPIO_Init(WR8080_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_WR引脚 */

//    gpio_init_struct.Pin = RD8080_GPIO_PIN;
//    HAL_GPIO_Init(RD8080_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RD引脚 */

//    gpio_init_struct.Pin = RS8080_GPIO_PIN;
//    HAL_GPIO_Init(RS8080_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RS引脚 */

//    gpio_init_struct.Pin = DATA8080_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
//    HAL_GPIO_Init(DATA8080_GPIO_PORT, &gpio_init_struct);   /* LCD_DATA引脚模式设置 */
//	
//	WR8080_Out(1);
//	RD8080_Out(1);
//	CS8080_Out(1);
//	RS8080_Out(1);
//	DATA8080_OUT(0XFFFF);
//	

//    /* 读取ID */
//    lcd_wr_regno(0xD3);
//    lcddev.id = lcd_rd_data();  /* 假读 */
//    lcddev.id = lcd_rd_data();  /* 00 */
//    lcddev.id = lcd_rd_data();  /* 93 */
//    lcddev.id <<= 8;
//    lcddev.id |= lcd_rd_data();  /* 41 */
//    
////    printf("lcddev_id:%#x \r\n", lcddev.id);
////    
//    /* 完成初始化序列 */
//    if (lcddev.id == 0x9341)
//        lcd_ex_ili9341_reginit();   
//    
//	/* 对LCD控制结构体赋值 */
//    lcddev.width = 240;
//    lcddev.height = 320;
//    lcddev.setxcmd = 0x2A;
//    lcddev.setycmd = 0x2B;
//    lcddev.wramcmd = 0x2C;
//    
//    lcd_wr_regno(lcddev.setxcmd);
//    lcd_wr_data(0);
//    lcd_wr_data(0);
//    lcd_wr_data((lcddev.width - 1) >> 8);
//    lcd_wr_data((lcddev.width - 1) & 0XFF);
//    lcd_wr_regno(lcddev.setycmd);
//    lcd_wr_data(0);
//    lcd_wr_data(0);
//    lcd_wr_data((lcddev.height - 1) >> 8);
//    lcd_wr_data((lcddev.height - 1) & 0XFF);
//    
//    /* 设置扫描方向 */
//    lcd_write_reg(0x36, 1 << 3);
////    
//    /* 点亮背光 */
//    LCD_BL_Out(1);
//    
//    /* lcd_clear */
//    lcd_clear(0xFFFF);

// }


