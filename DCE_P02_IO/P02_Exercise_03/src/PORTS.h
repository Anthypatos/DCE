/**
	@file	PORTS.h
	@author Juan de la Cruz Caravaca Guerrero
	@date	11/04/2021
	@brief	Header file describing the name of the ports for 
			this project.
	@par	Description 
			Allows to easily modify the pins with the LED connected.
			For other MCU only this header file will need to be 
			modified.
*/

#ifndef PORTS_H_
#define PORTS_H_

///MCU Port where devices are connected. Mode Configuration register.
#define GPIO_PORT_MODE DDRD

///Pin of port where the LED is connected. Configured as output.
#define LED_PIN_MODE DDD3

///MCU port where devices are connected. Output register.
#define GPIO_OUT PORTD

///Pins where devices are connected.
#define BUTTON_RPULLUP PORTD2
#define LED_PIN PORTD3

///MCU Port where devices are connected. Input register.
#define GPIO_IN PIND

///Pin of port where the pushbutton is connected.
#define BUTTON_PIN PIND2

#endif /* PORTS_H_ */