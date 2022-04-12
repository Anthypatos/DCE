/**
	@file	main.c
	@author Juan de la Cruz Caravaca Guerrero
	@date	28/03/2022
	@brief	Blinking the LED connected to pin 3 (Arduino).
	@par	Description 
			Pin 3 in Arduino is connected to pin 3 in PORTD.
			This information can be got from the picture showing 
			Arduino UNO <--> Atmega328p
*/

/// Define CPU frequency as 16 MHz 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/** ------------ SETUP ------------------ */
	/// 1) Set pin 3 in PORTD as output pin 
	DDRD |= (1 << DDD3);
	
	/** ------------ LOOP -------------------
				For blinking LED 
	-------------------------------------*/
	while (1)
	{
		/// 1) LED OFF by clearing the pin PD3
		PORTD &= ~(1 << PORTD3);
		
		/// 2) Delay of 500 milli-seconds
		_delay_ms(500);
		
		/// 3) LED ON by setting the pin PD3
		PORTD |= (1 << PORTD3);
		
		/// 4) Delay of 500 milli-seconds
		_delay_ms(500);
	}
}