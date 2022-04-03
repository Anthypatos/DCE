#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

#define FOSC		16000000 				// ARduino UNO Clock frequency
#define BAUD		9600
#define UBRR_VALUE	((F_CPU / (16UL * BAUD)) - 1)	// Prescaler to achieve 9600bps

void USART0_putchar(unsigned char data);
void USART0_putString(char *strPointer);
char USART0_getChar(void);

inline static void USART0_Init(uint16_t valueUBRR)
{
    /// -------------  SETUP -----------------------------------
	//1.-Set baud rate
	UBRR0H = (unsigned char)(UBRR_VALUE>>8);
	UBRR0L = (unsigned char)UBRR_VALUE;
	//2.-Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//3.-Set the speed: Normal Asynchronous
	//4.-Set frame format: 8data, 1stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00); 
}

#endif