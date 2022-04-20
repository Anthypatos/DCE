/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		19/04/2022
    @brief		
    @par		Description 
				
*/

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/USART.h"
#include "PORTS.h"

int main()
{
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	USART0_Init(UBRR_VALUE);
	
	uint16_t reading = ADC_Read_Single_Poll(ADC1);
	char strPointer[7] = "";
	
	while(1)
	{	
		reading = ADC_Read_Single_Poll(ADC1);
		
		if (reading <= 255) GPIO_B_OUT = (1 << LED0_PIN);
		else if (reading <= 512) GPIO_B_OUT = (1 << LED1_PIN);
		else if (reading <= 768) GPIO_B_OUT = (1 << LED2_PIN);
		else if (reading <= 1023) GPIO_B_OUT = (1 << LED3_PIN);
		
		USART0_putString(strcat(utoa(reading, strPointer, 10), "\n\r"));
	}
}