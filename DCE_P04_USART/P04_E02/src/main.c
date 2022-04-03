/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		30/03/2022
    @brief		"Hello world"
    @par		Description 
				Send the message "Hello world" through the USART by using polling technique.
				9600 8N1 is the configuration.
*/

#define  F_CPU	16000000UL
#include <avr/io.h>	 			
#include <util/delay.h>
#include <stdio.h>
#include "../../../DCE_Libraries/USART.h"

int main(){
	
	USART0_Init(UBRR_VALUE);
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1)	
    {	
		USART0_putchar(USART0_getChar());
	}
}