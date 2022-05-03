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
#include <stdlib.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/EXT_INT.h"
#include "../../../DCE_Libraries/USART.h"
#include "../../../DCE_Libraries/MACROS.h"

static inline void mainMenu();
static inline uint16_t ADC_avgRead(uint8_t channel, uint8_t samples);

static volatile uint16_t reading = 0;

ISR(ADC_vect)
{
	reading += ADC;
}


int main()
{
	// Setup
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	USART0_Init(UBRR_VALUE);
	
	ADC_Read(ADC0);	// First reading is slower
	
	mainMenu();
	char key = ' ';
	char strPointer[5] = "";
	
	// Superloop
	while(1)
	{
		if (CHECKBIT(UCSR0A, RXC0))
		{
			key = UDR0;
			
			switch (key)
			{
				case '1':	
					USART0_putString(utoa(ADC_avgRead(ADC0, SAMPLE16), strPointer, 10));
					USART0_putString("\n\r");
					break;
				case '2':
					USART0_putString(utoa(ADC_avgRead(ADC1, SAMPLE16), strPointer, 10));
					USART0_putString("\n\r");
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

static inline void mainMenu()
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

static inline uint16_t ADC_avgRead(uint8_t channel, uint8_t samples)
{
	reading = 0;
	
	for (uint8_t i = 0; i < samples; i++)
	{
		ADC_Read(channel);
		_delay_ms(500);
	}
	
	switch(samples)
	{
		case SAMPLE2: reading >>= 1; break;
		case SAMPLE4: reading >>= 2; break;
		case SAMPLE8: reading >>= 3; break;
		case SAMPLE16: reading >>= 4; break;
		default: break;
	}
	
	return reading;
}
