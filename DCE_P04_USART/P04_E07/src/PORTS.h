/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allows to easily modify the pin with the LED connected.
				For other MCU only this header file will need be modified.
*/


#ifndef PORTS_H_
#define PORTS_H_

#include <avr/io.h>

///MCU Port where the LED are connected. Mode Configuration register.
#define GPIO_B_MODE		DDRB

///Pin where every LED is connected.
#define LED0_PIN		PORTB0
#define LED1_PIN		PORTB1
#define LED2_PIN		PORTB2
#define LED3_PIN		PORTB3

///MCU ports where the LED and the pushbuttons are connected.
#define GPIO_B_OUT		PORTB
#define GPIO_D_OUT		PORTD	

///MCU port where the PUSHBUTTONS are connected.
#define GPIO_D_IN		PIND

///Pin where the BUTTONS are connected.
#define BUTTON0_PIN		PIND2
#define BUTTON1_PIN		PIND3

///Pull-up for PUSHBUTTONS
#define BUTTON0_RPULLUP	PORTD2
#define BUTTON1_RPULLUP PORTD3

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void GPIO_config(void)
{
	/// 1) LED as output
	GPIO_B_MODE |= (1 << LED0_PIN) | (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);

	/// 2) Enable Pull-up for Pushbuttons
	GPIO_D_OUT |= (1 << BUTTON0_RPULLUP) | (1 << BUTTON1_RPULLUP);
}

#endif /* PORTS_H_ */