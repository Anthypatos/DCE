/**
	@file main
	@author Juan de la Cruz Caravaca Guerrero
	@date 03/04/2022
	@brief LEDs behavior changes according to the state of a pushbutton.
	@par Description:
	The LEDs and the PUSHBUTTON are connected to the PORT 
	specified in "PORTS.h" 
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"

int main(void)
{
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Set LED pins as output. PUSHBUTTON LED is input by default. 
	GPIO_PORT_MODE |= (1 << LED_PIN_MODE) | (1 << LED2_PIN_MODE) | (1 << LED3_PIN_MODE) | (1 << LED4_PIN_MODE);
	
	/// 2) Enable pull-up for the PUSHBUTTON 
	GPIO_OUT |= (1 << BUTTON_RPULLUP);
	
	/** ------------ LOOP ----------------------------------------
	Read the state of the pushbutton and make the LEDs behave.
	Keep in mind that the read value when the PUSHBUTTON
	is released is '1' due to the pull-up resistor.
	----------------------------------------------------------*/
	while (1)
	{
		/// 1) Read pushbutton
		/// 2) If PUSHBUTTON is pressed
		if (!(GPIO_IN & (1 << BUTTON_PIN))) 
		{
			// ------------------------------------------------------------------
			// If (XXXX X1XX & 0000 0100 = 0000 0100) ? PIND2='1' (released)
			// If (XXXX X0XX & 0000 0100 = 0000 0000) ? PIND2='0' (pressed)
			// 0x00 -> FALSE Something non-zero ->TRUE.
			//--------------------------------------------------------------------

			/// Blink LEDs
			GPIO_OUT |= (1 << LED_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN) | (1 << LED4_PIN);
			_delay_ms(500);
			
			GPIO_OUT &= ~((1 << LED_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN) | (1 << LED4_PIN));
			_delay_ms(500);
		}
		else 
		{
			/// 3) else switch ON odd LEDs and OFF even ones
			/// NOTE: all PORTD pins are disabled at this point because of the if-else structure
			/// Hence, performing an OR operation on PORTD is a valid solution since the
			/// pull-up resistor on PORTD2 stays ON
			GPIO_OUT |= (1 << LED_PIN) | (1 << LED3_PIN);
		}
	}
}
