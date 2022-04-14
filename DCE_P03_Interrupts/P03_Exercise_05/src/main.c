/**
    @file	main.c
    @author Juan de la Cruz Caravaca Guerrero
    @date	13/04/2022
    @brief	Toggle a LED by means of PCINT interrupt.
    @par	Description:
			Toggle a RED LED with a pushbutton by means of pin change
            interrupts (PCINT18).
            The main program is blinking a GREEN LED.
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
    //Para que solo conmute si ha cambiado de '1' a '0'
	if (READ_PIN(GPIO_D_IN, BUTTON_PIN) == READ_FALSE) // If PIND2='0', pressed
        TOGGLE(GPIO_D_OUT, RED_LED_PIN); // Toggle the RED_LED
}


int main(void) 
{
    /** ------------ SETUP ----------------------------------------*/
    /// 1) Configure ports
    GPIO_config();

    /// 2) Configure external interrupt
    PCINT2_enable(); // PCINT2 is enabled
    PCINT2_enableBit(PCINT18); // Enable the ISR of PCINT18;

    /// 3) Enable global interrupts
    sei(); // Equivalent to SREG |= (1 << I);

    /** ------------ LOOP ----------------------------------------*/
    while (1)
    {
        _delay_ms(BLINK_TIME);
        TOGGLE(GPIO_D_OUT, GREEN_LED_PIN);  // Blinking LED_GREEN
    }   // End while (1)
}   // End main()
