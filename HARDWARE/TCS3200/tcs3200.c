#include "sys.h"
#include "tcs3200.h"
#include "exti.h"
#include "delay.h"

u8 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount;
u16 wbarr[3] = {0};

void tcs3200_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;   //OUT_pin
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   //RES_pin
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{
	EXTI4_Init();		 //外部中断初始化
	S2=0;S3=0;//红色通道
	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子 
	wbarr[0] = Rgena;
	amount=0;
//----------------------------------
	S2=1;S3=1;//绿色通道
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
	wbarr[1] = Ggena;
	amount=0;
//----------------------------------
	S2=0;S3=1;//蓝色通道
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
	wbarr[2] = Bgena;
	amount=0;
	S2=1;S3=0;//关闭通道  	  
}  

u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	Ramount=(u32) amount*255/Rgena;	 //取R值
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//取G值
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//去B值
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
} 

