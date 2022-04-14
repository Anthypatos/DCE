/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		14/04/2022
    @brief		USART and INT0
    @par		Description 
				Every time a pushbutton is pressed (bouncing is ignored), show onto the screen 
				the message "Hello World". (INT0 interrupt - UDRE interrupt)
*/

#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include "PORTS.h"	
#include "..\..\..\DCE_Libraries\EXT_INT.h"	
#include "..\..\..\DCE_Libraries\USART.h"
#include "..\..\..\DCE_Libraries\MACROS.h"

/// -------------  ISR functions -----------------------------------
ISR (INT0_vect)
{
	USART0_enaInterrupt_TX();
}
//-------------------------------------------------------------------

ISR (USART_UDRE_vect)
{
	char *strPointer = "Hello world\n\r";
	
	//-------------------------------------------------------------
	// SOL_1: Not blocking
	//-------------------------------------------------------------
	while (*strPointer)
	{
		if (CHECKBIT(UCSR0A, UDRE0))
		{	
			// (Polling for TX) Only sends if the buffer is empty ('1')
			UDR0 = *strPointer;				// Send the data
			
			strPointer++;
		}
	}
	//-------------------------------------------------------------	
	/*
	// SOL_2 - Blocking
	USART0_putString("Hello World\n\r");	// BLOCKING!!! due to the "while" in the function.
	//-------------------------------------------------------------
	*/
	
	USART0_disableInterrupt_TX();
}
//-------------------------------------------------------------------

int main()
{
	/// -------------  SETUP -----------------------------------
	/// 1. Config ports (Pushbutton - "PORTS.h")
	GPIO_config();
	
	//---------------------------------------------------------
	/// 2. External interrupt setup (INT0 - Pushbutton)
	INT0_config(FALLING);
	INT0_enable();
	
	//----------------------------------------------------------
	/// 3. USART setup (9600 8N1 - Keyboard)
	USART0_Init(UBRR_VALUE);
	
	//----------------------------------------------------------
	/// 4. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1);
}

