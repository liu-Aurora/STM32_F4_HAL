//#include "Delay.h"

////利用系统滴答定时，编写的延时函数

//static uint8_t  fac_us=0; //us延时倍乘数			   

///****************************************************************************
//* 名    称: delay_init()
//* 功    能：延时函数初始化
//* 入口参数：无
//* 返回参数：无
//* 说    明：
//****************************************************************************/
//void delay_init()
//{
//	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTick频率为HCLK
//	fac_us=SYSCLK;					
//}								    

///****************************************************************************
//* 名    称: void delay_us(u32 nus)
//* 功    能：延时nus
//* 入口参数：要延时的微妙数
//* 返回参数：无
//* 说    明：nus的值,不要大于798915us
//****************************************************************************/
//void delay_us(uint32_t nus)
//{		
//	uint32_t ticks;
//	uint32_t told,tnow,tcnt=0;
//	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
//	ticks=nus*fac_us; 						//需要的节拍数 
//	told=SysTick->VAL;        				//刚进入时的计数器值
//	while(1)
//	{
//		tnow=SysTick->VAL;	
//		if(tnow!=told)
//		{	    
//			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
//		}  
//	}; 
//}

///****************************************************************************
//* 名    称: void delay_ms(u16 nms)
//* 功    能：延时nms
//* 入口参数：要延时的毫妙数
//* 返回参数：无
//* 说    明： 
//****************************************************************************/
//void delay_ms(uint16_t nms)
//{
//	uint32_t i;
//	for(i=0;i<nms;i++) delay_us(1000);
//} 