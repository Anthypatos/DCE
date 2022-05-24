/**
	@file		WHEELS.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		18/05/2022
    @brief		Header file including functions to configure the wheels.
*/

#ifndef WHEELS_H_
#define WHEELS_H_

#include <avr/io.h>
#include <stdint.h>
#include "TMR4.h"
#include "MACROS.h"

void Robot_FWD(uint8_t speedLeft, uint8_t speedRight);
void Robot_BWD(uint8_t speedLeft, uint8_t speedRight);
void Robot_STOP();
void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight);
void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight);


// Initializes the wheels
static inline void setupWheels()
{
	SETBIT(DDRD, DDD6);
	SETBIT(DDRE, DDE6);
	TMR4_PWM_Phase_Init();
}


#endif /* WHEELS_H_ */