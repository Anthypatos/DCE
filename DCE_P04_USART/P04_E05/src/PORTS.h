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
static inline void GPIO_config(void)
{
	/// 1) Enable Pull-up for Pushbutton
	GPIO_D_OUT	|= (1 << BUTTON_RPULLUP);
}

#endif /* PORTS_H_ */