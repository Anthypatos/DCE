/**
	@file	main.c
	@author Juan de la Cruz Caravaca Guerrero
	@date	28/03/2022
	@brief	Turning on the LEDs according to binary numbers.
	@par	Description 
			Sending to the LEDs the binary values equivalent 
            to the range 0-F.
*/

/// Define CPU frequency as 16 MHz 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"
#include "PARAMETERS.h"

int main(void)
{
	/** ------------ SETUP ------------------ */
	/// 1) Set pins 2, 3, 4, 5, 7 in PORTD as output pin 
	LED_PORT_MODE |= (1 << LED_PIN_MODE) | (1 << LED2_PIN_MODE) | (1 << LED3_PIN_MODE) | 
		(1 << LED4_PIN_MODE) || (1 << LED5_PIN_MODE);

    int counter = 0;
	
	/** ------------ LOOP -------------------
				For blinking LED 
	-------------------------------------*/
	
	while (1)
	{
		/// 1) LED ON or OFF by setting the pins PD2, PD3, PD4, PD5
        // PD7 is always ON
		LED_PORT = 0x80 | (counter << 2);

        // 2) Range of the counter is 0 to 9
        counter = (counter + 1) % 10;
		
		/// 3) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
	}
}