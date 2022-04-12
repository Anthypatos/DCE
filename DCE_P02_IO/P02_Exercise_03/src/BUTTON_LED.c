/**
	@file BUTTON_LED.c
	@author Mirian Cifredo
	@date 10/02/2022
	@brief The state of a pushbutton is shown in a LED.
	@par Description:
	The LED and the PUSHBUTTON is connected to the PORT 
	specified in "PORTs.h" 
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include "PORTS.h"

int main(void)
{
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Set LED pin as output. PUSHBUTTON LED is input by default. 
	GPIO_PORT_MODE |= (1 << LED_PIN_MODE);

	/// 2) Enable pull-up for the PUSHBUTTON 
	GPIO_OUT |= (1 << BUTTON_RPULLUP);

	/** ------------ LOOP ----------------------------------------
	Read the state of the pushbutton and shows it onto a LED.
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
			// If (XXXX X1XX & 0000 0100 = 0000 0100)  PIND2='1' (released)
			// If (XXXX X0XX & 0000 0100 = 0000 0000)  PIND2='0' (pressed)
			// 0x00 -> FALSE Something non-zero ->TRUE.
			//--------------------------------------------------------------------

			/// Switch ON LED
			GPIO_OUT |= (1 << LED_PIN);
		}
		else
		{
			/// 3) else switch OFF LED
			GPIO_OUT &= (~(1 << LED_PIN));
		}
	}
}
