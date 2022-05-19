/**
	@file		TMR1.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		03/05/2022
    @brief		Header file including functions to configure the Timer 1.
*/

#ifndef TMR1_H_
#define TMR1_H_

#include <stdint.h>
#include <avr/io.h>

#define DIV_CLK_NONE	1
#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5


static inline void TMR1_CTC_Init(void)
{
	// Set TMR1 Mode as CTC on OCR1A
	TCCR1B &= ~(1 << WGM13);
	TCCR1B |= (1 << WGM12);
	TCCR1A &= ~((1 << WGM11) | (WGM10));
}

static inline void TMR1_CTC_Set(uint16_t value) 
{ 
	// Set the matching value in OCR1A
	OCR1A = value;
}

static inline void TMR1_CTC_Start(uint8_t divClk) 
{
	// 1.- Clear the flag (not necessary in CTC with ISR)
	TIFR1 |= (1 << OCF1A);
	
	TCNT1 = 0;
	
	// 2.- Set the prescaler and start
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); 
	TCCR1B |= divClk; 
}
static inline void TMR1_CTC_Stop(void) { TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); }
	
static inline void TMR1_HW_toggleOC1A(void)
{
	//1.- It is mandatory to set OC1A as output (Pin PB5)
	DDRB |= (1 << DDB5);
	//2.- Set Toggle as the hardware output in OC1A
	TCCR1A &= ~(1 << COM1A1);	// Toggle OC1A on Compare Match.
	TCCR1A |= (1 << COM1A0);	// Toggle OC1A on Compare Match.
}

#endif	/* TMR1_H_ */