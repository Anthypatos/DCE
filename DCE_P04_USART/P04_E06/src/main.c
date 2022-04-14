/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		14/04/2022
    @brief		USART and INT0
    @par		Description 
				Every time a letter is pressed, show onto the screen 
				the equivalent capital letter. (RX interrupt - UDRE interrupt)
*/

#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include "..\..\..\DCE_Libraries\EXT_INT.h"	
#include "..\..\..\DCE_Libraries\USART.h"

static volatile char key = ' ';

/// -------------  ISR functions -----------------------------------
ISR (USART_RX_vect)
{
	key = UDR0;
	
	if (key >= 0x61 && key <= 0x7A)
	{
		key -= 0x20;
		USART0_enaInterrupt_TX();
	}
}
//-------------------------------------------------------------------

ISR (USART_UDRE_vect)
{
	UDR0 = key;
	
	USART0_disableInterrupt_TX();
}
//-------------------------------------------------------------------

int main()
{
	//----------------------------------------------------------
	/// 1. USART setup (9600 8N1 - Keyboard)
	USART0_Init(UBRR_VALUE);
	USART0_enaInterrupt_RX();
	
	//----------------------------------------------------------
	/// 2. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1);
}

