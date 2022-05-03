/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		20/04/2022
    @brief		LDR
    @par		Description
				Reads the value of an LDR to toggle a LED
				
*/

#define F_CPU		16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/EXT_INT.h"
#include "../../../DCE_Libraries/MACROS.h"
#include "PORTS.h"
#include "PARAMETERS.h"

static volatile uint16_t reading = 0;

ISR(ADC_vect)
{
	reading = ADC;
}


int main()
{
	// Setup
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	sei();
	ADC_enaInterrupt();

	ADC_Read(ADC0);	// First reading is slower
	
	// Superloop
	while(1)
	{
		// Reads the value
		ADC_Read(ADC0);
		
		// Toggles the LED accordingly
		if (reading < SETPOINT) GPIO_B_OUT = (1 << LED0_PIN);
		else GPIO_B_OUT = 0x00;
		
		_delay_ms(SAMPLE_TIME);
	}
}