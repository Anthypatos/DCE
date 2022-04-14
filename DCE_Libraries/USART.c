#define  F_CPU	16000000UL
#include <avr/io.h>	 			
#include <util/delay.h>
#include "USART.h"

/// ----------- FUNCTIONS -------------
void USART0_putchar(unsigned char data)
{
	// (Polling) Wait for empty transmit buffer/register
	
	// While the bit UDRE0 is '0' keeps waiting
	// (there is a transmission in progress, wait...)
	while (!( UCSR0A & (1<<UDRE0)));
	
	// When UDRE0=1, the USART is available for transmitting.
	// Write the data to send in the register.
	UDR0 = data;
}


void USART0_putString(char *strPointer)
{
	// (Polling) While the NULL char (end of line) is not reached
	// send a new character of the string.
	while(*strPointer)
	{
		USART0_putchar(*strPointer);
		strPointer++;
	}	
}

char USART0_getChar(void)
{
    // Polling
    while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
}