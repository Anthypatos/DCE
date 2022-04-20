/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		20/04/2022
    @brief		
    @par		Description 
				
*/

#define F_CPU		16000000UL

#define SAMPLE1		1
#define SAMPLE2		2
#define SAMPLE4		4
#define SAMPLE8		8
#define SAMPLE16	16

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/EXT_INT.h"
#include "../../../DCE_Libraries/USART.h"
#include "../../../DCE_Libraries/MACROS.h"

static volatile uint16_t reading = 0;

inline static void mainMenu();
inline static uint16_t ADC_avgRead(uint8_t channel, uint8_t samples);

ISR(ADC_vect)
{
	reading += ADC;
}


int main()
{
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	USART0_Init(UBRR_VALUE);
	sei();
	
	reading = ADC_Read_Single_Poll(ADC0);
	ADC_enaInterrupt();
	
	mainMenu();
	char key = ' ';
	char strPointer[7] = "";
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1)
	{
		if (CHECKBIT(UCSR0A, RXC0))
		{
			key = UDR0;
			
			switch (key)
			{
				case '1':
					USART0_putString(strcat(utoa(ADC_avgRead(ADC0, SAMPLE4), strPointer, 10), "\n\r"));
					break;
				case '2':
					USART0_putString(strcat(utoa(ADC_avgRead(ADC1, SAMPLE4), strPointer, 10), "\n\r"));
					break;
				case 'h':
					mainMenu();
					break;
				default:
					USART0_putString("I don't know what to do with that key\n\r");
					break;
			}
		}
	}
}

inline static void mainMenu()
{
	USART0_putString("\f-----------------------------------------------\n\r"
	"This is the main menu. Select one choice:\n\r"
	"-----------------------------------------------\n\r"
	"1.- Measure of the LDR\n\r"
	"2.- Measure of the potentiometer\n\r"
	"\n\r"
	"h.- Show the menu again\n\r"
	"-----------------------------------------------\n\r");
}

inline static uint16_t ADC_avgRead(uint8_t channel, uint8_t samples)
{
	reading = 0;
	
	for (uint8_t i = 0; i < samples; i++)
	{
		// 1. Clear the flag asserted in a previous readout
		ADCSRA |= (1 << ADIF);
		
		// 2. Clear the channel to set a new one
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
		
		// 3. Set the channel
		ADMUX |= channel;
		
		// 4. Start a conversion for the selected channel
		ADCSRA |= (1 << ADSC);
		
		_delay_ms(500);
	}
	
	switch(samples)
	{
		case SAMPLE2:
			reading >>= 1;
			break;
		case SAMPLE4:
			reading >>= 2;
			break;
		case SAMPLE8:
			reading >>= 3;
			break;
		case SAMPLE16:
			reading >>= 4;
			break;
		default:
			break;
	}
	
	return reading;
}