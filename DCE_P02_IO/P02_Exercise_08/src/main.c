/**
	@file	main.c
	@author	Juan de la Cruz Caravaca Guerrero
	@date	12/04/2022
    @brief	The state of a LED is changed by means of a push button.
    @par	Description:
			A LED is toggled by means of a debounced pushbutton by using a FSM.			
*/

#define F_CPU	16000000UL

#include <util/delay.h>
#include <stdbool.h>
#include "PORTS.h"
#include "../../../DCE_Libraries/MACROS.h"
#include "../../../DCE_Libraries/functionsGPIO.h"

//---------  User data types definitions -------------
typedef enum 
{
	STATE_LED_ON,
	BLINK_STATE,
	STATE_LED_OFF
} State_t;


int main(void) 
{
	/**---------  Local variables (Registers) -----------------*/
	/// Variable to keep the state of the FSM
	static State_t state		= STATE_LED_ON;
	
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
		readButton 	= read_input(GPIO_D_IN, BUTTON_PIN);
		//-----------------------------------------------------------

		/// 2. The TRANSITIONS and the OUTPUT are combined
		/// in a single switch-case. Therefore, the "nextState"
		/// variable is not needed.
		switch(state)
		{
			case STATE_LED_ON:
				if (readButton == READ_FALSE) state = BLINK_STATE;
				SETBIT(GPIO_D_OUT, LED_PIN);
				break;

			case BLINK_STATE:
				if (readButton == READ_FALSE) state = STATE_LED_OFF;
				TOGGLE(GPIO_D_OUT, LED_PIN);
				_delay_ms(BLINK_TIME);
				break;

			case STATE_LED_OFF:
				if (readButton == READ_FALSE) state = STATE_LED_ON;
				CLEARBIT(GPIO_D_OUT, LED_PIN);
				break;

			default:
				state = STATE_LED_ON;
				break;
		} // Close Switch-Transitions
		//------------------------------------------------------------------------
	}	// Close While
} 	// Close Main
