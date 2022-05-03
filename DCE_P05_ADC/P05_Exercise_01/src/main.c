/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		19/04/2022
    @brief		Potentiometer
    @par		Description
				Reads the value of the potentiometer, sends it through
				the USART and lights 4 LEDs accordingly
				
*/

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/USART.h"
#include "PORTS.h"

int main()
{
	// Setup
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	USART0_Init(UBRR_VALUE);
	
	uint16_t reading = ADC_Read_Single_Poll(ADC1);	// First reading is slower
	char strPointer[5] = "";
	
	// Superloop
	while(1)
	{	
		// Reads the value
		reading = ADC_Read_Single_Poll(ADC1);
		
		// Sets the right LED
		if (reading <= 255) GPIO_B_OUT = (1 << LED0_PIN);
		else if (reading <= 512) GPIO_B_OUT = (1 << LED1_PIN);
		else if (reading <= 768) GPIO_B_OUT = (1 << LED2_PIN);
		else if (reading <= 1023) GPIO_B_OUT = (1 << LED3_PIN);
		
		// Shows the value on the screen
		USART0_putString(utoa(reading, strPointer, 10));
		USART0_putString("\n\r");
	}
}