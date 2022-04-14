/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		14/04/2022
    @brief		Echo test
    @par		Description
				Shows on the screen the same character received 
				from the keyboard via USART.
				
*/

#include "../../../DCE_Libraries/USART.h"

int main()
{	
	USART0_Init(UBRR_VALUE);
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1) USART0_putchar(USART0_getChar());
}