/**
	@file		main_noBlocking.c
	@author		Mirian Cifredo
	@date		10/02/2022
    @brief		Toggle a LED by means a pushbutton
    @par		Description 
				Allow toggle a LED every time a pushbutton is pressed.
				In order to avoid a bouncing in the pushbutton, the system waits for a time
				until the state of the pushbutton is stable.
*/

/// Define CPU frequency as 16 MHz 
#define  F_CPU	16000000UL

#include <avr/io.h>	 			
#include <util/delay.h>
#include <stdbool.h>
#include "PORTS.h" 
#include "PARAMETERS.h"
#include "MACROS.h"


int main(void)
{
	/** ------------ SETUP ------------------------*/
	///	1) Set pin as output
	GPIO_MODE |= (1 << LED_PIN);	
	
	/// 2) Enable pull-up for the PUSHBUTTON 
	GPIO_OUT |= (1 << BUTTON_RPULLUP);
	
	/** ------------ LOOP ----------------------------------------*/
	while (1)
	{
		static bool flag					= true;
		bool button_CurrentState			= true; 

		button_CurrentState = READ_PIN(GPIO_IN, BUTTON_PIN);
		
		if (button_CurrentState == BUTTON_NOT_PRESSED) flag = BUTTON_NOT_PRESSED;
		
		_delay_ms(100); // Wait for a second reading
		
		button_CurrentState = READ_PIN(GPIO_IN, BUTTON_PIN); // Second reading
		
		if ((button_CurrentState == BUTTON_PRESSED) && (flag == BUTTON_NOT_PRESSED)) // Falling-edge
		{
			_delay_ms(20); // Debouncing time
			button_CurrentState = READ_PIN(GPIO_IN, BUTTON_PIN); // Third reading
			if (button_CurrentState == BUTTON_PRESSED)
			{
				//flag = false;
				flag = BUTTON_PRESSED; // se da por buena la acción de la pulsación y se restaura para aceptar una nueva pulsación
				GPIO_OUT ^= (1 << LED_PIN);	
			}
		}
	}
}
