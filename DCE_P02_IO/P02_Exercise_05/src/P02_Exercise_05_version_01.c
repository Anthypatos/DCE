/**
	@file		main.c
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
		///	1) If the pushbutton is pressed
		 if (READ_PIN(GPIO_IN,BUTTON_PIN)==BUTTON_PRESSED)
		 {
			///			* Wait for a time to avoid bouncing in pushbutton
			_delay_ms(DEBOUNCE_TIME);				
			///			* Wait while button keeps pressed
			while(READ_PIN(GPIO_IN,BUTTON_PIN)==BUTTON_PRESSED);
			/// 2) When the pushbutton is released, does the task: change the state of the LED
			 GPIO_OUT ^= (1 << LED_PIN);	
			_delay_ms(DEBOUNCE_TIME);		
		 } 
	 }
	 
 }

