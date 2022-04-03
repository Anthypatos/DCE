/**
	@file main
	@author Juan de la Cruz Caravaca Guerrero
	@date 03/04/2022
	@brief LEDs behavior change according to the state of a pushbutton.
	@par Description:
	The LEDs and the PUSHBUTTON are connected to the PORT 
	specified in "PORTs.h" 
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Set LED pins as output. PUSHBUTTON LED is input by default. 
	DDRD |= (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6);
	
	/// 2) Enable pull-up for the PUSHBUTTON 
	PORTD |= (1 << PORTD2);
	
	/** ------------ LOOP ----------------------------------------
	Read the state of the pushbutton and make the LEDs behave.
	Keep in mind that the read value when the PUSHBUTTON
	is released is '1' due to the pull-up resistor.
	----------------------------------------------------------*/
	while (1)
	{
		/// 1) Read pushbutton
		/// 2) If PUSHBUTTON is pressed
		if (!(PIND & (1 << PIND2))) 
		{
			// ------------------------------------------------------------------
			// If (XXXX X1XX & 0000 0100 = 0000 0100) ? PIND2='1' (released)
			// If (XXXX X0XX & 0000 0100 = 0000 0000) ? PIND2='0' (pressed)
			// 0x00 -> FALSE Something non-zero ->TRUE.
			//--------------------------------------------------------------------

			/// Blink LEDs
			PORTD |= (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6);
			_delay_ms(500);
			
			PORTD &= ~((1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6));
			_delay_ms(500);
		}
		else 
		{
			/// 3) else switch ON odd LEDs and OFF even ones
			PORTD = (1 << PORTD3) | (1 << PORTD5);
		}
	}
}
