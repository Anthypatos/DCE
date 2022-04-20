/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		20/04/2022
    @brief		
    @par		Description 
				
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
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	sei();
	
	reading = ADC_Read_Single_Poll(ADC0);
	ADC_enaInterrupt();
	
	while(1)
	{
		// 1. Clear the flag asserted in a previous readout
		ADCSRA |= (1 << ADIF);
		
		// 2. Clear the channel to set a new one
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
		
		// 3. Set the channel
		ADMUX |= ADC0;
		
		// 4. Start a conversion for the selected channel
		ADCSRA |= (1 << ADSC);
		
		if (reading < SETPOINT) GPIO_B_OUT = (1 << LED0_PIN);
		else GPIO_B_OUT = 0x00;
		
		_delay_ms(SAMPLE_TIME);
	}
}