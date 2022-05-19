#ifndef TMR0_H_
#define TMR0_H_

#include <stdint.h>
#include <avr/io.h>

#define DIV_CLK_NONE	1
#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5


static inline void TMR0_CTC_Init(void)
{
	// Set TMR1 Mode as CTC on OCR0A
	TCCR1B &= ~(1 << WGM02);
	TCCR1A |= (1 << WGM01);
    TCCR1A &= ~(1 << WGM00);
}


static inline void TMR0_CTC_Set(uint16_t value) 
{ 
	// Set the matching value in OCR0A
	OCR0A = value;
}


static inline void TMR0_CTC_Start(uint8_t divClk) 
{
	// 1.- Clear the flag (not necessary in CTC with ISR)
	TIFR0 |= (1 << OCF0A);
	
	TCNT0 = 0;
	
	// 2.- Set the prescaler and start
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); 
	TCCR0B |= divClk; 
}


static inline void TMR0_CTC_Stop(void) { TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); }
	

static inline void TMR0_HW_toggleOC0A(void)
{
	//1.- It is mandatory to set OC0A as output (Pin PD6)
	DDRD |= (1 << DDD6);
	//2.- Set Toggle as the hardware output in OC0A
	TCCR0A &= ~(1 << COM0A1);	// Toggle OC0A on Compare Match.
	TCCR0A |= (1 << COM0A0);	// Toggle OC0A on Compare Match.
}


static inline void TMR0_PWM_Phase_Init(void)
{
    DDRD |= (1 << DDD5) | (1 << DDD6);

    TCCR0B &= ~(1 << WGM02);
	TCCR0A &= ~(1 << WGM01);
    TCCR0A |= (1 << WGM00);

    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);
    TCCR0A |= (1 << COM0B1);
    TCCR0A &= ~(1 << COM0B0);
}


static inline void TMR0_PWM_Phase_Start(uint8_t divClock)
{
    TCNT0 = 0; //Set Initial Timer value
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (CS00));
    TCCR0B |= divClock;
}


static inline void TMR0_PWM_Phase_Duty(uint8_t valueOCR0A, uint8_t valueOCR0B)
{
    OCR0A = valueOCR0A;
    OCR0B = valueOCR0B;
}

#endif