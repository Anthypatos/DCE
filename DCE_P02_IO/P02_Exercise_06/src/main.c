/**
	@file	main.c
	@author	Mirian Cifredo
	@date	10/02/2022
    @brief	The state of a LED is changed by means of a push button.
    @par	Description:
			A LED is toggled by means of a debounced pushbutton by using a FSM. 
			Only the bouncing when pushing the button is taken into account.				
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
	/**---------  Local variables (Registers) -----------------*/
	/// Variables to keep the state of the FSM
	static State_t state		= STATE_START;	
	static State_t Next_state	= STATE_START;
	
	/// Variable to read the button and store as TRUE/FALSE
	bool readButton				= READ_TRUE;	


	/**------------ SETUP--------------------------------------*/
	/// 1) Ports are configured.
	configPorts();

	/**---------- SUPERLOOP (FSM) -----------------------------*/
	while (1) 
	{
		/// 1. Check the EVENT in each iteration
		// The value for "state" is preserved. (Static variable)
		readButton 	= READ_PIN(GPIO_D_IN, BUTTON_PIN);

		//-----------------------------------------------------------
		/// 2. Set the TRANSITIONS based upon events
		switch(state)
		{
			case STATE_START:
				// When the pushbutton is pressed then...
				if (readButton == READ_FALSE) Next_state = STATE_TIMER;
				break;

			case STATE_TIMER:
				// Wait until timer finishes, then...
				_delay_ms(DEBOUNCE_TIME);
				Next_state = STATE_RELEASE;
				break;

			case STATE_RELEASE:
				// Wait until the push is released (HIGH), then...
				if (readButton == READ_TRUE) Next_state = STATE_DEBOUNCED;
				break;

			case STATE_DEBOUNCED:
				// Without conditions
				Next_state = STATE_START;
				break;

			default:
				Next_state = STATE_START;
				break;
		} // Close Switch-Transitions
		//------------------------------------------------------------------------

		/// 3. Set the OUTPUTS in every state. Nothing to do in any state but the
		/// "STATE_DEBOUNCED" one.
		switch (state) 
		{
			case STATE_START:
				break;
				
			case STATE_TIMER:
				break;
				
			case STATE_RELEASE:
				break;

			case STATE_DEBOUNCED:	
				TOGGLE(GPIO_D_OUT, LED_PIN);
				break;
				
			default:
				break;
		}	// Close Switch-Outputs
		//--------------------------------------------------------------------------

		// 4. UPDATE state
		state = Next_state;
		//--------------------------------------------------------------------------	
	}	// Close While
} 	// Close Main
