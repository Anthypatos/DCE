/**
    @file	main.c
    @author Juan de la Cruz Caravaca Guerrero
    @date	13/04/2022
    @brief	The state of a pushbutton is shown in a LED
    @par	Description:
			The LED and the PUSHBUTTON are connected to the PORT 
			specified in "PORTs.h". A RED_LED is switch ON/OFF 
			by means a push button while a GREEN_LED is always 
			blinking. 
			In this version, the pushbutton is connected to an 
			external interrupt.
*/

#define F_CPU			16000000UL
#define MAX_INCREMENT	4

#include <avr/interrupt.h>
#include <util/delay.h>
#include "PORTS.h"
#include "../../../DCE_Libraries/EXT_INT.h"


typedef enum
{
	allOn,
	oddOn,
	evenOn,
	allOff
} State_t;

static volatile State_t state = allOn;


/**-------- Interrupt Service Routines --------------------------*/
/// If INT0 interrupt is enabled, each time the pushbutton is 
/// pressed, the int interrupt is triggered. Then all the actions 
/// written into the ISR are executed. When it finishes, the flag is 
/// cleared and the main program continues.
ISR(INT0_vect) 
{
    _delay_ms(200); // To avoid the bouncing. Not recommend. 
    state = allOn;
}


int main(void) 
{
    /** ------------ SETUP ----------------------------------------*/
    /// 1) Configure ports
    configPorts();

    /// 2) Configure external interrupt
    INT0_config(FALLING); // INT0 is triggered by a falling edge
    INT0_enable(); // Enable the ISR of INT0;

    /// 3) Enable global interrupts
    sei(); // Equivalent to SREG |= (1 << I);

    /** ------------ LOOP ----------------------------------------*/
    while (1) 
	{ 
		switch(state)
		{
			case allOn:
				state = oddOn;
				GPIO_D_OUT = 0xF4;
				break;
			case oddOn:
				state = evenOn;
				GPIO_D_OUT = 0xA4;
				break;
			case evenOn:
				state = allOff;
				GPIO_D_OUT = 0x54;
				break;
			case allOff:
				state = allOn;
				GPIO_D_OUT = 0x04;
				break;
			default:
				state = allOn;
				break;
		}
		
		_delay_ms(2000);
	}
}
