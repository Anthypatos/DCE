/**
    @file	main.c
    @author Juan de la Cruz Caravaca Guerrero
    @date	13/04/2022
    @brief	The state of a pushbutton is shown in a LED
    @par	Description:
			The LED and the PUSHBUTTON are connected to the PORT 
			specified in "PORTS.h". A RED_LED is switch ON/OFF 
			by means of a push button while a GREEN_LED is always 
			blinking. 
			In this version, the pushbutton is connected to an 
			external interrupt.
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PORTS.h"
#include "..\..\..\DCE_Libraries\MACROS.h"
#include "..\..\..\DCE_Libraries\EXT_INT.h"


/**-------- Interrupt Service Routines --------------------------*/
/// If PCINT2 interrupt is enabled, each time the pushbutton is 
/// pressed, the int interrupt is triggered. Then all the actions 
/// written into the ISR are executed. When it finishes, the flag is 
/// cleared and the main program continues.
ISR(PCINT2_vect) 
{
    _delay_ms(200); // To avoid the bouncing. Not recommend.
	if (READ_PIN(GPIO_D_IN, BUTTON_PIN) == READ_FALSE) TOGGLE(GPIO_D_OUT, RED_LED_PIN); // Toggle the RED_LED
}


int main(void) 
{
    /** ------------ SETUP ----------------------------------------*/
    /// 1) Configure ports
    configPorts();

    /// 2) Configure external interrupt
    PCINT2_enable(); // PCINT2 is enabled
    PCINT2_enableBit(PCINT18); // Enable the ISR of PCINT18;

    /// 3) Enable global interrupts
    sei(); // Equivalent to SREG |= (1 << I);

    /** ------------ LOOP ----------------------------------------*/
    while (1)
    {
        TOGGLE(GPIO_D_OUT, GREEN_LED_PIN);
        _delay_ms(BLINK_TIME);
    }
}
