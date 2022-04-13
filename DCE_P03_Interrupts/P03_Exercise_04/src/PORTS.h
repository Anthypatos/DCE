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

///MCU Port where the LED is connected. Mode Configuration register.
#define GPIO_D_MODE		DDRD

///Pin where every LED is connected.
#define LED_PIN			PORTD4
#define LED2_PIN		PORTD5
#define LED3_PIN		PORTD6
#define LED4_PIN		PORTD7

///MCU port where the LED is connected.
#define GPIO_D_OUT		PORTD	

///MCU port where the PUSHBUTTON is connected.
#define GPIO_D_IN		PIND

///Pin where the BUTTON is connected.
#define BUTTON_PIN		PIND2

///Pull-up for PUSHBUTTON
#define BUTTON_RPULLUP	PORTD2

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void configPorts(void)
{
	/// 1) LED as output
	GPIO_D_MODE |= (1 << LED_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN) | (1 << LED4_PIN);

	/// 2) Enable Pull-up for Pushbutton
	GPIO_D_OUT |= (1 << BUTTON_RPULLUP);
}

#endif /* PORTS_H_ */