#define F_CPU	16000000UL

#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "functionsGPIO.h"
#include "MACROS.h"

bool read_input(uint8_t portGPIO, uint8_t pinNumber) 
{ 
	static bool flag					= true;
	bool button_CurrentState			= true;

	button_CurrentState = READ_PIN(portGPIO, pinNumber);
	
	if (button_CurrentState == READ_TRUE) flag = READ_TRUE;
	
	_delay_ms(DEBOUNCE_TIME); // Wait for a second reading
	
	button_CurrentState = READ_PIN(portGPIO, pinNumber); // Second reading
	
	if ((button_CurrentState == READ_FALSE) && (flag == READ_TRUE)) // Falling-edge
	{
		_delay_ms(DEBOUNCE_TIME); // Debouncing time
		button_CurrentState = READ_PIN(portGPIO, pinNumber); // Third reading
		if (button_CurrentState == READ_FALSE)
		{
			//flag = false;
			flag = READ_FALSE; // se da por buena la acción de la pulsación y se restaura para aceptar una nueva pulsación
			return READ_FALSE;
		}
	}

	return READ_TRUE;
}