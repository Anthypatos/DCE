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

///MCU ports where the LED are connected.
#define GPIO_B_OUT		PORTB

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void GPIO_config(void)
{
	/// 1) LED as output
	GPIO_B_MODE |= (1 << LED0_PIN) | (1 << LED1_PIN);
}

#endif /* PORTS_H_ */