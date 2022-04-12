/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/


#ifndef PORTS_H_
#define PORTS_H_
///MCU Port where the LED is connected. Mode Configuration register.
#define GPIO_D_MODE		DDRD
///Pin where GREEN LED is connected.
#define LED0	PORTD3
///Pin where RED LED is connected.
#define LED1		PORTD4
#define LED2		PORTD5
#define LED3		PORTD6
///MCU port where the LED are connected.
#define GPIO_D_OUT		PORTD	
///MCU port where the PUSHBUTTON is connected.
#define GPIO_D_IN		PIND
///Pin where the BUTTON is connected.
#define BUTTON_PIN		PIND2
///Pull-up for PUSHBUTTON
#define BUTTON_RPULLUP	PORTD2

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void GPIO_config(void){
	/// 1) LED as output
	GPIO_D_MODE |= (1<<LED0)|(1<<LED1)|(1<<LED2)|(1<<LED3);
	/// 2) Enable Pull-up for Pushbutton
	GPIO_D_OUT	|= (1<<BUTTON_RPULLUP);
	
}

#endif /* PORTS_H_ */