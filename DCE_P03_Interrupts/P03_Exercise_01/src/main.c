/**
    @file	main.c
    @author Mirian Cifredo
    @date	07/03/2022
    @brief	The state of a pushbutton is shown in a LED
    @par	Description:
			The LED and the PUSHBUTTON are connected to the PORT 
			specified in "PORTs.h". A RED_LED is switch ON/OFF 
			by means a push button while a GREEN_LED is always 
			blinking. 
			In this version, the pushbutton is connected to an 
			external interrupt.
*/

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include "PORTS.h"
#include "..\..\..\DCE_Libraries\MACROS.h"


/**-------- Interrupt Service Routines --------------------------*/
/// If INT0 interrupt is enabled, each time the pushbutton is 
/// pressed, the int interrupt is triggered. Then all the actions 
/// written into the ISR are executed. When it finishes, the flag is 
/// cleared and the main program continues.
ISR(INT0_vect) 
{
    _delay_ms(200); // To avoid the bouncing. Not recommend. 
    TOGGLE(GPIO_D_OUT, RED_LED_PIN); // Toggle the RED_LED
}


int main(void) 
{
    /** ------------ SETUP ----------------------------------------*/
    /// 1) Configure ports
    configPorts();

    /// 2) Configure external interrupt
    EICRA |= (1 << ISC01); // INT0 is triggered by a falling edge
    EICRA &= ~(1 << ISC00); // ISC01-00 = "10"
    EIMSK |= (1 << INT0); // Enable the ISR of INT0;

    /// 3) Enable global interrupts
    sei(); // Equivalent to SREG |= (1 << I);

    /** ------------ LOOP ----------------------------------------*/
    while (1)
    {
        TOGGLE(GPIO_D_OUT, GREEN_LED_PIN);
        _delay_ms(BLINK_TIME);
    }
}
