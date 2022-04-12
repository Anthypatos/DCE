/**
	@file	main.c
	@author	Mirian Cifredo
	@date	10/02/2022
    @brief	The state of a LED is changed by means a push button.
    @par	Description:
			A LED is toggled by means of a debounced pushbutton by using a FSM. 				
*/

#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "PORTS.h"
#include "PARAMETERS.h"
#include "../../../DCE_VARIOS/MACROS.h"

//---------  User data types definitions -------------
typedef enum 
{
	STATE_START,
	STATE_TIMER,
	STATE_RELEASE,
	STATE_DEBOUNCED
} State_t;


int main(void) 
{
	/**---------  Local variables ----------------------*/
	/// Variable to keep the state of the FSM
	static State_t state		= STATE_START;	

	/// Variable to read the button and store as TRUE/FALSE
	bool readButton		= READ_TRUE;	

	/**------------ SETUP------------------------------*/
	/// 1) Ports are configured.
	configPorts();

	/**---------- SUPERLOOP ---------------------------*/
	while (1) 
	{
		/// 1. Check the EVENT in each iteration
		// The value for "state" is preserved.
		readButton 	= READ_PIN(GPIO_D_IN,BUTTON_PIN);

		/// 2. The TRANSITIONS and the OUTPUT are combined
		/// in a single switch-case. Therefore, the "nextState"  
		/// variable is not needed.
		switch (state) 
		{
			case STATE_START:
				// Wait here until the pushbutton is pressed 
				if (readButton == READ_FALSE) state = STATE_TIMER;
				break;

			case STATE_TIMER:
				_delay_ms(DEBOUNCE_TIME);
				// a) Debouncing the pressed button
				if (readButton == READ_FALSE) state = STATE_RELEASE;
				// b) Debouncing the released button
				else state = STATE_DEBOUNCED;
				break;
				
			case STATE_RELEASE:
				// Wait until the push is released (HIGH)
				if (readButton == READ_TRUE) // For debouncing the released button
					state = STATE_TIMER; 
				break;

			case STATE_DEBOUNCED:	
				TOGGLE(GPIO_D_OUT, LED_PIN);
				state = STATE_START;
				break;
				
			default:
				state = STATE_START;
				break;
		}	// Close Switch
	}	// Close While
} 	// Close Main
