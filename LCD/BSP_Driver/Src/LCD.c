//#include "LCD.h"
//#include "8080.h"

///* ����LCD��Ҫ���� */
//_lcd_dev lcddev;

///* LCD�Ļ�����ɫ�ͱ���ɫ */
//uint32_t g_point_color = 0XF800;    	/* ������ɫ */
//uint32_t g_back_color  = 0XFFFF;    	/* ����ɫ */

//void lcd_wr_data(uint16_t data)
//{
//    RS8080_Out(1);
//	CS8080_Out(0);
//	DATA8080_OUT(data);
//	WR8080_Out(0);
//	WR8080_Out(1);
//	CS8080_Out(1);
//}  

///* 8080 д���� */
//void lcd_wr_regno(uint16_t command)
//{
//    RS8080_Out(0);
//	CS8080_Out(0);
//	DATA8080_OUT(command);
//	WR8080_Out(0);
//	WR8080_Out(1);
//	CS8080_Out(1);
//}

///* ���Ĵ���дֵ */
//void lcd_write_reg(uint16_t regno, uint16_t data)
//{
//    WR_Reg_8008(regno);    /* д��Ҫд�ļĴ������ */
//    WR_Data_8080(data);      /* д������ */
//}

//static void lcd_opt_delay(uint32_t i)
//{
//    while(i--);
//}

///* LCD������ */
//uint16_t lcd_rd_data(void)
//{
//    volatile uint16_t ram;  /* ��ֹ���Ż� */
//    
//    GPIO_InitTypeDef gpio_init_struct;
//    /* LCD_DATA ����ģʽ����, ��������, ׼���������� */
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
//    /* LCD_DATA ����ģʽ����, �������, �ָ����״̬ */
//    gpio_init_struct.Pin = DATA8080_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
//    gpio_init_struct.Pull = GPIO_PULLUP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(DATA8080_GPIO_PORT, &gpio_init_struct);   

//    return ram;
//}

///* ׼��дGRAM */
//void lcd_write_ram_prepare(void)
//{
//    WR_Reg_8008(lcddev.wramcmd);
//}

///* �������� */
//void lcd_set_cursor(uint16_t x, uint16_t y)
//{
//    lcd_wr_regno(lcddev.setxcmd);
//    lcd_wr_data(x >> 8);
//    lcd_wr_data(x & 0xFF);
//    lcd_wr_regno(lcddev.setycmd);
//    lcd_wr_data(y >> 8);
//    lcd_wr_data(y & 0xFF);
//}

///* ���� */
//void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
//{
//    lcd_set_cursor(x, y);
//    lcd_write_ram_prepare();
//    lcd_wr_data(color);
//}

///* ���� */
//uint16_t  lcd_read_point (uint16_t x, uint16_t y)
//{
//    uint16_t r = 0, g = 0, b = 0;   /* ������� */
//    
//    lcd_set_cursor(x, y);           /* �������� */
//    lcd_wr_regno(0X2E);             /* ���������� */
//    r = lcd_rd_data();              /* �ٶ� */
//    r = lcd_rd_data();              /* ��rg */
//    b = lcd_rd_data();              /* ��b */
//    g = r & 0XFF;                   /* �õ�gֵ */
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
//    totalpoint *= lcddev.height;    /* �õ��ܵ��� */
//    lcd_set_cursor(0, 0);   		/* ���ù��λ�� */
//    lcd_write_ram_prepare();        /* ��ʼд��GRAM */

//    RS8080_Out(1);                      /* RS=1,��ʾд���� */
//    CS8080_Out(0);
//    
//    for (index = 0; index < totalpoint; index++)
//    {
//        DATA8080_OUT(color);        /* д��Ҫд������ */
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
//	CS8080_GPIO_CLK_ENABLE();    /* LCD_CS��ʱ��ʹ�� */
//	WR8080_GPIO_CLK_ENABLE();    /* LCD_WR��ʱ��ʹ�� */
//	RS8080_GPIO_CLK_ENABLE();    /* LCD_RS��ʱ��ʹ�� */
//	RD8080_GPIO_CLK_ENABLE();    /* LCD_RD��ʱ��ʹ�� */
//	LCD_BL_GPIO_CLK_ENABLE();	 /* LCD_BL��ʱ��ʹ�� */
//	DATA8080_GPIO__CLK_ENABLE(); /* LCD_DATA��ʱ��ʹ�� */
//	
//	gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ���츴�� */
//    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
//    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL����ģʽ����(�������) */

//    gpio_init_struct.Pin = CS8080_GPIO_PIN;
//    HAL_GPIO_Init(CS8080_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_CS���� */

//    gpio_init_struct.Pin = WR8080_GPIO_PIN;
//    HAL_GPIO_Init(WR8080_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_WR���� */

//    gpio_init_struct.Pin = RD8080_GPIO_PIN;
//    HAL_GPIO_Init(RD8080_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RD���� */

//    gpio_init_struct.Pin = RS8080_GPIO_PIN;
//    HAL_GPIO_Init(RS8080_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RS���� */

//    gpio_init_struct.Pin = DATA8080_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
//    HAL_GPIO_Init(DATA8080_GPIO_PORT, &gpio_init_struct);   /* LCD_DATA����ģʽ���� */
//	
//	WR8080_Out(1);
//	RD8080_Out(1);
//	CS8080_Out(1);
//	RS8080_Out(1);
//	DATA8080_OUT(0XFFFF);
//	

//    /* ��ȡID */
//    lcd_wr_regno(0xD3);
//    lcddev.id = lcd_rd_data();  /* �ٶ� */
//    lcddev.id = lcd_rd_data();  /* 00 */
//    lcddev.id = lcd_rd_data();  /* 93 */
//    lcddev.id <<= 8;
//    lcddev.id |= lcd_rd_data();  /* 41 */
//    
////    printf("lcddev_id:%#x \r\n", lcddev.id);
////    
//    /* ��ɳ�ʼ������ */
//    if (lcddev.id == 0x9341)
//        lcd_ex_ili9341_reginit();   
//    
//	/* ��LCD���ƽṹ�帳ֵ */
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
//    /* ����ɨ�跽�� */
//    lcd_write_reg(0x36, 1 << 3);
////    
//    /* �������� */
//    LCD_BL_Out(1);
//    
//    /* lcd_clear */
//    lcd_clear(0xFFFF);

// }


