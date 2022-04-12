/**
	@file		main.c
	@author		Mirian Cifredo
	@date		15/03/2022
    @brief		USART and INT0
    @par		Description 
				a) Every time a pushbutton is pressed (bouncing is ignored), show onto the screen 
				the following ASCII char is a range from 0x20 to 0x7E. (Tx polling - INT0 interrupt)
				b) Show on 4 LED the ASCII equivalent to a key hit on the keyboard. (Rx Interrupts)
*/

#define  F_CPU	16000000UL
#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include "PORTS.h"	
#include "..\..\..\DCE_LIBRARIES\EXT_INT.h"	
#include "..\..\..\DCE_LIBRARIES\USART.h" 

/// -------------  ISR functions -----------------------------------
// For fulfill the a) requirement
ISR (INT0_vect)
{
	static char datum = 0x21;
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending 
	//-------------------------------------------------------------
	// SOL_1: Not blocking
	//-------------------------------------------------------------
	if (UCSR0A & (1 << UDRE0))
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
		if( datum >= 0x7F )
		{							// If the final character has been reached
			datum = 0x21;
		}							// Re-start "datum"
		else datum++;

	} // comment for solution 2
}
//-------------------------------------------------------------------
// For fulfill the b) requirement
ISR (USART_RX_vect)
{
	//-----------------------------------------------------------------------------
	// 1.- Clear the 4MSB in PORTD. The remaining bits keep the value (Rpull-up)
	// Then, OR with the 4LSB of the ASCII and shifts the value for showing
	// onto the LED.
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
	while(1)
	{
				
	}
}

