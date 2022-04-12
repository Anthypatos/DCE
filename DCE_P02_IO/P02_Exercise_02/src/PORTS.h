/**
	@file	PORTS.h
	@author Juan de la Cruz Caravaca Guerrero
	@date	12/04/2021
	@brief	Header file describing the name of the ports for 
			this project.
	@par	Description 
			Allows to easily modify the pins with the LED connected.
			For other MCU only this header file will need be 
			modified.
*/

#ifndef PORTS_H_
#define PORTS_H_

///MCU Port where the LED are connected. Mode Configuration register.
#define LED_PORT_MODE 	DDRD

///Pins of port where the LED are connected. Configured as output.
#define LED_PIN_MODE 	DDD2
#define LED2_PIN_MODE 	DDD3
#define LED3_PIN_MODE 	DDD4
#define LED4_PIN_MODE 	DDD5
#define LED5_PIN_MODE 	DDD7

///MCU port where the LED are connected. 
#define LED_PORT 		PORTD

///Pins where the LED are connected.
#define LED_PIN 		PORTD2
#define LED2_PIN 		PORTD3
#define LED3_PIN 		PORTD4
#define LED4_PIN 		PORTD5
#define LED5_PIN 		PORTD7

#endif /* PORTS_H_ */