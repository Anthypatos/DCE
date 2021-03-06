/**
	@file		main.c
	@author		Mirian Cifredo
	@date		15/03/2022
    @brief		USART and INT0
    @par		Description 
				a) Every time a pushbutton is pressed (bouncing is ignored), show onto the screen 
				the following ASCII char in a range from 0x20 to 0x7E. (Tx polling - INT0 interrupt)
				b) Show on 4 LED the ASCII equivalent to a key hit on the keyboard. (Rx Interrupts)
*/

#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include "PORTS.h"	
#include "..\..\..\DCE_Libraries\EXT_INT.h"	
#include "..\..\..\DCE_Libraries\USART.h"
#include "..\..\..\DCE_Libraries\MACROS.h"

/// -------------  ISR functions -----------------------------------
// For fulfilling the a) requirement
ISR (INT0_vect)
{
	static char datum = 0x20;
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending 
	//-------------------------------------------------------------
	// SOL_1: Not blocking
	//-------------------------------------------------------------
	if (CHECKBIT(UCSR0A, UDRE0))
	{	
		// (Polling for TX) Only sends if the buffer is empty ('1')
		UDR0 = datum;				// Send the data
		//-------------------------------------------------------------	
		/*	
		// SOL_2 - Blocking
		USART0_putchar(datum);			// BLOCKING!!! due to the "while" in the function.
		//-------------------------------------------------------------
		*/	
		//------------------------------------------------------------------
		// 2.- If the char has been sent, increment the ASCII while is in the range.
		//-----------------------------------------------------------------
		if(datum >= 0x7E) // If the final character has been reached
			datum = 0x20; // Re-start "datum"
		else datum++;
	}
}
//-------------------------------------------------------------------

// For fulfilling the b) requirement
ISR (USART_RX_vect)
{
	//-----------------------------------------------------------------------------
	// 1.- Clear the 4MSB in PORTD. The remaining bits keep their value (Rpull-up)
	// Then, OR with the 4LSB of the ASCII and shifts the value to show
	// on the LED.
	PORTD = (PORTD & 0b00001111) | ((UDR0 & 0x0F) << 4);
}

//-------------------------------------------------------------------

int main()
{
	/// -------------  SETUP -----------------------------------
	/// 1. Config ports (4 LED and pushbutton - "PORTS.h")
	GPIO_config();
	
	//---------------------------------------------------------
	/// 2. External interrupt setup (INT0 - Pushbutton)
	INT0_config(FALLING);
	INT0_enable();
	
	//----------------------------------------------------------
	/// 3. USART setup (9600 8N1 - Keyboard)
	USART0_Init(UBRR_VALUE);
	USART0_enaInterrupt_RX();
	
	//----------------------------------------------------------
	/// 4. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1);
}

