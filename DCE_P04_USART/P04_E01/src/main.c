/**
	@file		main.c
	@author		Mirian Cifredo
	@date		13/03/2022
    @brief		"Hello world"
    @par		Description 
				Send the message "Hello world" through the USART by using the polling technique.
				9600 8N1 is the configuration.
*/

#define  F_CPU	16000000UL

#include <avr/io.h>	 			
#include <util/delay.h>

#define FOSC		16000000 						// Arduino UNO Clock frequency
#define BAUD		9600
#define UBRR_VALUE	((F_CPU / (16UL * BAUD)) - 1)	// Prescaler to achieve 9600bps

void USART0_putchar(unsigned char data);
void USART0_putString(char *strPointer);

int main()
{	
	/// -------------  SETUP -----------------------------------
	//1.-Set baud rate
	UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
	UBRR0L = (unsigned char)UBRR_VALUE;

	//2.-Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	//3.-Set the speed: Normal Asynchronous
	//4.-Set frame format: 8data, 1stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1) USART0_putString("Hello world \n\r");
}


void USART0_putchar(unsigned char data)
{
	// (Polling) Wait until the transmit buffer/register is empty

	// While the bit UDRE0 is '0' keeps waiting
	// (there is a transmission in progress, wait...)
	while (!( UCSR0A & (1<<UDRE0)));

	// When UDRE0=1, the USART is available for transmitting.
	// Write the data to be sent in the register.
	UDR0 = data;
}


void USART0_putString(char *strPointer)
{
	// While the NULL char (end of line) is not reached
	// send a new character of the string.
	while(*strPointer)
    {
		USART0_putchar(*strPointer);
		strPointer++;
	}	
}