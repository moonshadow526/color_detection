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
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)
{
	EXTI4_Init();		 //�ⲿ�жϳ�ʼ��
	S2=0;S3=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	delay_ms(10);
	Rgena = amount;   //�����ɫ���� 
	wbarr[0] = Rgena;
	amount=0;
//----------------------------------
	S2=1;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //�����ɫ����
	wbarr[1] = Ggena;
	amount=0;
//----------------------------------
	S2=0;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //�����ɫ����
	wbarr[2] = Bgena;
	amount=0;
	S2=1;S3=0;//�ر�ͨ��  	  
}  

u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	Ramount=(u32) amount*255/Rgena;	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//ȥBֵ
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
} 

