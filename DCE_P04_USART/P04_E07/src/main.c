/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		14/04/2022
    @brief		USART, INT0 and INT1
    @par		Description 
				a) Every time a pushbutton is pressed (bouncing is ignored), show onto the screen 
				the previous or next ASCII char in a range from 0x20 to 0x7E. (Tx polling - INT0 interrupt - INT1 interrupt)
				b) Show on 4 LED the amount of times one of the pushbuttons was pressed.
*/

#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include <stdint.h>
#include "PORTS.h"	
#include "..\..\..\DCE_Libraries\EXT_INT.h"	
#include "..\..\..\DCE_Libraries\USART.h"
#include "..\..\..\DCE_Libraries\MACROS.h"

static volatile char datum = 0x7E;
static volatile uint8_t counter = 0;

/// -------------  ISR functions -----------------------------------
ISR (INT0_vect)
{
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending
	//-------------------------------------------------------------
	if (CHECKBIT(UCSR0A, UDRE0))
	{
		// (Polling for TX) Only sends if the buffer is empty ('1')
		UDR0 = datum;				// Send the data
		
		//------------------------------------------------------------------
		// 2.- If the char has been sent, increment the ASCII while is in the range.
		//-----------------------------------------------------------------
		if(datum >= 0x7E) // If the final character has been reached
			datum = 0x20; // Re-start "datum"
		else datum++;
	}
	
	counter = (counter + 1) % 16;
}

ISR(INT1_vect)
{
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending
	//-------------------------------------------------------------
	if (CHECKBIT(UCSR0A, UDRE0))
	{
		// (Polling for TX) Only sends if the buffer is empty ('1')
		UDR0 = datum;		// Send the data
		
		//------------------------------------------------------------------
		// 2.- If the char has been sent, increment the ASCII while is in the range.
		//-----------------------------------------------------------------
		if(datum <= 0x20) // If the final character has been reached
			datum = 0x7E; // Re-start "datum"
		else datum--;
	}
}

//-------------------------------------------------------------------

int main()
{
	/// -------------  SETUP -----------------------------------
	/// 1. Config ports (4 LED and pushbuttons - "PORTS.h")
	GPIO_config();
	
	//---------------------------------------------------------
	/// 2. External interrupt setup (INT0 - INT1 -Pushbuttons)
	INT0_config(FALLING);
	INT0_enable();
	
	INT1_config(FALLING);
	INT1_enable();
	
	//----------------------------------------------------------
	/// 3. USART setup (9600 8N1 - Keyboard)
	USART0_Init(UBRR_VALUE);
	
	//----------------------------------------------------------
	/// 4. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1) GPIO_B_OUT = counter;
}
