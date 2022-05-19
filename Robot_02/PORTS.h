/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allows to easily modify the pins with devices connected.
				For other MCU only this header file will need be modified.
*/


#ifndef PORTS_H_
#define PORTS_H_

#include <avr/io.h>

///MCU Port where devices are connected. Mode Configuration register.
#define GPIO_B_MODE		DDRB

///Pins where devices are connected.
#define BUZZER			DDB2

///MCU ports where the BUZZER is connected.
#define GPIO_B_OUT		PORTB

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void GPIO_config(void)
{
	/// 1) BUZZER as output
	GPIO_B_MODE |= (1 << BUZZER);
}

#endif /* PORTS_H_ */