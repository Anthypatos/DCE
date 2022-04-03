/**
	@file	BlinkLED_13.c
	@author Mirian Cifredo
	@date	23/12/2021
	@brief	Blinking the LED connected to pin 13 (Arduino).
	@par	Description 
			Pin 13 in Arduino is connected to pin 5 in PORTB.
			This information can be got from the picture showing 
			Arduino UNO <--> Atmega328p
*/

/// Define CPU frequency as 16 MHz 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"
#include "PARAMETERS.h"

int main(void)
{
	/** ------------ SETUP ------------------ */
	/// 1) Set pin 5 in PORTB as output pin 
	DDRB |=(1<<DDB5);
	
	/** ------------ LOOP -------------------
				For blinking LED 
	-------------------------------------*/
	
	while (1)
	{
		/// 1) LED OFF by clearing the pin PB5
		PORTB &=~(1<<PORTB5);
		
		/// 2) Delay of 500 milli-seconds
		_delay_ms(500);
		
		/// 3) LED ON by setting the pin PB5
		PORTB |=(1<<PORTB5);
		
		/// 4) Delay of 500 milli-seconds
		_delay_ms(500);
	}
}