#ifndef TEST_BUZZER_H
#define TEST_BUZZER_H

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU			16000000UL

#define STARTING_SOUND	2
#define MATCH_SOUND		1
#define FAIL_SOUND		4

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "MACROS.h"


static inline void playSound(uint8_t delay)
{
	SETBIT(PORTB, PORTB2);
	_delay_ms(delay);
	CLEARBIT(PORTB, PORTB2);
	_delay_ms(delay);
}

#endif