/*
 * main.c
 *
 *  Created on: Nov 18, 2020
 *      Author: Abeer
 */
#include"util/delay.h"
#include "lib/BIT_MATH.h"
#include "lib/STD_Types.h"
#include "lib/AVR32_REG.h"
#include "DIO/DIO_Interface.h"
#include "ADC/ADC_Interface.h"
#include "LCD/Lcd_Interface.h"
#include "LM35/LM35_Interface.h"
#include"UART/UART_Intereface.h"

void Display_tempLCD(){
	f32 temp;
	LCD_VidInit();
	LM35_Init();

	while(1){
		LCD_VidClearDisplay();
		LM35_VidRead(&temp);
		LCD_VidPrintFloatNumber(temp);
				LCD_VidSendData('C');
				_delay_ms(1000);
	}
}

void Num_Send_TTL(u16 num){
	u16 rev_num=0,local_num=num;
	u8 ZeroAscii=48;
	while(local_num){
		rev_num=(rev_num*10)+local_num%10;
		local_num/=10;
	}
	while(rev_num){
		UART_VidSend((rev_num%10)+ZeroAscii);
		rev_num/=10;
	}
}
void Display_tempTTL(){
	f32 temp;
	u16 t;
  		LM35_Init();
 		DIO_VidSetPortDirection(PORTD, 0x02);
 		UART_VidInit(ASYNC_NORM_BAUD, 9600);
		while(1){
 			LM35_VidRead(&temp);
 			t=(u16)temp;
 			Num_Send_TTL(t);
 			UART_VidSend('C');
 			_delay_ms(1000);

		}
}

int main()
{

Display_tempTTL();
 }







