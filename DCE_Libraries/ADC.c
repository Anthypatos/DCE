/**
	@file		functionsADC.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		19/04/2022
    @brief		Functions to configure the ADC
				
*/

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <avr/io.h>
#include "MACROS.h"
#include "ADC.h"

//----------------------------------------------------------------------
uint16_t ADC_Read_Single_Poll(uint8_t channel)
{
	// 1. Clear the flag asserted in a previous readout
	ADCSRA |= (1 << ADIF);
	
	// 2. Clear the channel to set a new one
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
	
	// 3. Set the channel
	ADMUX |= channel;
	
	// 4. Start a conversion for the selected channel
	ADCSRA |= (1 << ADSC);
	
	// 5. Wait the sample is read. (Polling the flag)
	while (CHECKBIT(ADCSRA, ADIF) == READ_FALSE);
	
	// 6. Return the 10-bit sample read in the ADC.
	return ADC;
}


void ADC_Read(uint8_t channel)
{
	// 1. Clear the flag asserted in a previous readout
	ADCSRA |= (1 << ADIF);
	
	// 2. Clear the channel to set a new one
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
	
	// 3. Set the channel
	ADMUX |= channel;
	
	// 4. Start a conversion for the selected channel
	ADCSRA |= (1 << ADSC);
}

#endif /* ADC_H_ */