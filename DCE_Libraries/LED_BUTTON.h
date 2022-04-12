/**
	@file		LED_BUTTON.h
	@author		Mirian Cifredo
	@date		27/02/2022
    @brief		Header file describing the parameters regarding to the project.
    @par		Description 
				Allows to easily modify the blinking time.
*/


#ifndef LED_BUTTON_H_
#define LED_BUTTON_H_

#define LED_TOGGLE(ADDRESS, BIT)	ADDRESS ^= (1 << BIT)
#define LED_ON(ADDRESS, BIT)		ADDRESS |= (1 << BIT)
#define LED_OFF(ADDRESS, BIT)		ADDRESS &= ~(1 << BIT)

#define	IS_PIN_ZERO(ADDRESS, BIT)	!(ADDRESS & (1 << BIT))	// Flag=0 --> TRUE
#define	READ_BUTTON(ADDRESS, BIT)	(ADDRESS & (1 << BIT))	// 
								
#define BUTTON_PRESSED				0
#define BUTTON_NOT_PRESSED			1

/// Time in ms the MCU waits for the bouncing in the pushbutton.
#define DEBOUNCE_TIME	100		

/// Time in ms the LED stays ON or OFF.
#define BLINK_TIME 500

#endif /* LED_BUTTON_H_ */