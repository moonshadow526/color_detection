# include <stdio.h>
# include <stdlib.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "SSD1331.h" 
#include "Fonts.h"
#include "tcs3200.h"
 
/************************************************
color_detection
************************************************/


int main(void)
 {		
	 u16 R=0,G=0,B=0;
	  char str_r[10] = {0};
		char str_g[10] = {0};
		char str_b[10] = {0};
		delay_init();	    	 //延时函数初始化	  
		uart_init(115200);	 //串口初始化为115200
		SPI2_Init();
		SPI2_SetSpeed(SPI_BaudRatePrescaler_2);
		ssd1331_init();
		tcs3200_init();
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		whitebalance();
//		ssd1331_clear_screen(RED);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		delay_ms(1000);
//		delay_ms(1000);
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//		ssd1331_clear_screen(GREEN);
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//		delay_ms(1000);
//		delay_ms(1000);
//		ssd1331_clear_screen(BLUE);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		delay_ms(1000);
//		delay_ms(1000);
		ssd1331_clear_screen(BLACK);

//		ssd1331_draw_bitmap(0, 2, &c_chSingal816[0], 16, 8, YELLOW);
//		ssd1331_draw_bitmap(19, 2, &c_chMsg816[0], 16, 8, YELLOW);
//		ssd1331_draw_bitmap(38, 2, &c_chBluetooth88[0], 8, 8, YELLOW);
//		ssd1331_draw_bitmap(52, 2, &c_chGPRS88[0], 8, 8, YELLOW);
//		ssd1331_draw_bitmap(66, 2, &c_chAlarm88[0], 8, 8, YELLOW);
//		ssd1331_draw_bitmap(80, 2, &c_chBat816[0], 16, 8, GREEN);

//		ssd1331_draw_3216char(8,16, '2', BLUE);
//		ssd1331_draw_3216char(24,16, '3', BLUE);
//		ssd1331_draw_3216char(40,16, ':', RED);
//		ssd1331_draw_3216char(56,16, '5', BLUE);
//		ssd1331_draw_3216char(72,16, '6', BLUE);
		
//		sprintf(str, "%d", Rgena);

//		ssd1331_display_string(9, 48, str, FONT_1608, GREEN);
//		ssd1331_clear_screen(BLACK);
//		ssd1331_draw_bitmap(0, 1, &gImage_1[0], 128, 64, WHITE);
	
while (1) 
{
		ssd1331_display_num(10, 32, wbarr[0],1,FONT_1608, RED);
		ssd1331_display_num(40, 32, wbarr[1],1,FONT_1608, GREEN);
		ssd1331_display_num(70, 32, wbarr[2],1,FONT_1608, BLUE);
		R = tcs3200_RED();
		G = tcs3200_GREEN();	//取RGB值
		B = tcs3200_BLUE();	 
		sprintf(str_r, "%d", R);
		sprintf(str_g, "%d", G);
		sprintf(str_b, "%d", B);
		ssd1331_display_string(10, 48, str_r, FONT_1608, RED);
		ssd1331_display_string(40, 48, str_g, FONT_1608, GREEN);
		ssd1331_display_string(70, 48, str_b, FONT_1608, BLUE);
		delay_ms(1000);
		ssd1331_clear_screen(BLACK);
	}

} 
 


