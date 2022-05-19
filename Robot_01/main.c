#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "PORTS.h"
#include "TEST_BUZZER.h"
#include "TMR0.h"
#include "TMR1.h"
#include "EXT_INT.h"


typedef enum
{
	STATE_START,
	STATE_MATCH,
	STATE_FAIL
} State_t;


static volatile State_t state = STATE_START;


ISR(TIMER0_COMPA_vect)
{
	switch(state)
	{
		case STATE_START:
			playSound(STARTING_SOUND);
			break;
		case STATE_MATCH:
			playSound(MATCH_SOUND);
			break;
		case STATE_FAIL:
			playSound(FAIL_SOUND);
			break;
	}
}


ISR(TIMER1_COMPA_vect)
{
	switch(state)
	{
		case STATE_START:
			state = STATE_MATCH;
			break;
		case STATE_MATCH:
			state = STATE_FAIL;
			break;
		case STATE_FAIL:
			TMR0_CTC_Stop();
			TMR1_CTC_Stop();
			break;
	}
}



int main(void)
{
	GPIO_config();
	sei();
	
	TMR0_CTC_Init();
	TMR0_CTC_Set(32);
	TMR0_CTC_EnaInterrupt();
	
	TMR1_CTC_Init();
	TMR1_CTC_Set(15625);
	TMR1_CTC_EnaInterrupt();
	
	TMR0_CTC_Start(DIV_CLK_1024);
	TMR1_CTC_Start(DIV_CLK_1024);
	
    while (1);
}

