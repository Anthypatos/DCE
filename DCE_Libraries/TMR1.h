/**
	@file		TMR1.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		19/04/2022
    @brief		Header file including functions to configure the TIMER1
*/

#ifndef TMR1_H_
#define TMR1_H_

#include <stdint.h>
#include <avr/io.h>

#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5


static inline void TMR1_CTC_Init()
{
	TCCR1B &= ~(1 << WGM13);
	TCCR1B |= (1 << WGM12);
	TCCR1A &= ~((1 << WGM11) | (WGM10));
}

static inline void TMR1_CTC_Set(uint16_t value) { OCR1A = value; }

static inline void TMR1_CTC_Start(uint8_t divClk) 
{
	TCNT1 = 0;
	
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); 
	TCCR1B |= divClk; 
}
static inline void TMR1_CTC_Stop() { TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); }
	
static inline void TMR1_HW_toggleOC1A()
{
	TCCR1A |= (1 << COM1A0);
	TCCR1A &= ~(1 << COM1A1);
}

#endif