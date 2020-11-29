/*
 * LM35_Program.c
 *
 *  Created on: Nov 21, 2020
 *      Author: Abeer Mohamed Hassan
 */
#include "../lib/BIT_MATH.h"
#include "../lib/STD_Types.h"
 #include "../DIO/DIO_Interface.h"
#include "../ADC/ADC_Interface.h"
#include "LM35_Config.h"
void LM35_Init(void)
{
	DIO_VidSetPinDirection(PortA,DIO_Pin0,Input);
	ADC_VidInit();
	ADC_VidSelectChannel(0);
	ADC_VidEnable();
}

void LM35_VidRead(f32 * Copy_U16Read)
{
	u16 ADC_Read;
	f32 ADC_StepSize,Analog_Read;
	ADC_Read=ADC_VidRead();
	ADC_StepSize=(f32)ADC_REFVCC/ADC_Resolution;
  	Analog_Read=(f32)ADC_StepSize*(ADC_Read);
 	*Copy_U16Read=ceil(Analog_Read/10 );
}


