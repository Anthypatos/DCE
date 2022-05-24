/**
	@file		TMR4.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		18/05/2022
    @brief		Header file including functions to configure the Timer 4.
*/

#ifndef TMR4_H_
#define TMR4_H_

#include <stdint.h>
#include <avr/io.h>
#include "MACROS.h"

#define TMR4_DIV_CLK_NONE	1
#define TMR4_DIV_CLK_2		2
#define TMR4_DIV_CLK_4		3
#define TMR4_DIV_CLK_8		4
#define TMR4_DIV_CLK_16		5
#define TMR4_DIV_CLK_32		6
#define TMR4_DIV_CLK_64		7
#define TMR4_DIV_CLK_128	8
#define TMR4_DIV_CLK_256	9
#define TMR4_DIV_CLK_512	10
#define TMR4_DIV_CLK_1024	11
#define TMR4_DIV_CLK_2048	12
#define TMR4_DIV_CLK_4096	13
#define TMR4_DIV_CLK_8192	14
#define TMR4_DIV_CLK_16384	15


static inline void TMR4_PWM_Phase_Init(void)
{
	// Set OC4A/PC6 and OC4D/PD7 as output
	SETBIT(DDRC, DDC6);
	SETBIT(DDRD, DDD7);

	//Clear OC4A/OC4D on compare match
	CLEARBIT(TCCR4A, COM4A1);
	SETBIT(TCCR4A, COM4A0);
	SETBIT(TCCR4C, COM4D1);
	CLEARBIT(TCCR4C, COM4D0);
	
	SETBIT(TCCR4A, PWM4A);
	SETBIT(TCCR4C, PWM4D);
	
	//Phase correct PWM mode
	CLEARBIT(TCCR4D, WGM41);
	SETBIT(TCCR4D, WGM40);
}


static inline void TMR4_PWM_Phase_Start(uint8_t divClock)
{
	//Set Initial Timer value
	TCNT4 = 0;

	//Set prescaler and start timer
	TCCR4B &= ~((1 << CS43) | (1 << CS42) | (1 << CS41) | (1 << CS40));
	TCCR4B |= divClock;
}


static inline void TMR4_PWM_Phase_Duty(uint8_t valueOCR4A, uint8_t valueOCR4D)
{
	//Compare values
	OCR4A = valueOCR4A;
	OCR4D = valueOCR4D;
}



#endif /* TMR4_H_ */