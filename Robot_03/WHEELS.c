/**
	@file		WHEELS.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		18/05/2022
    @brief		Functions for configuring the wheels
*/

#include <avr/io.h>
#include <stdint.h>
#include "WHEELS.h"
#include "TMR4.h"
#include "MACROS.h"

// Makes the robot move forward
void Robot_FWD(uint8_t speedLeft, uint8_t speedRight)
{
	CLEARBIT(PORTD, PORTD6);
	CLEARBIT(PORTE, PORTE6);
	TMR4_PWM_Phase_Duty(255 - speedLeft, speedRight);
}


// Makes the robot move backwards
void Robot_BWD(uint8_t speedLeft, uint8_t speedRight)
{
	SETBIT(PORTD, PORTD6);
	SETBIT(PORTE, PORTE6);
	TMR4_PWM_Phase_Duty(255 - speedLeft, speedRight);
}


// Makes the robot stop
void Robot_STOP() { TMR4_PWM_Phase_Duty(255, 0); }


// Makes the robot turn right
void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight)
{
	CLEARBIT(PORTD, PORTD6);
	SETBIT(PORTE, PORTE6);
	TMR4_PWM_Phase_Duty(255 - speedLeft, speedRight);
}


// Makes the robot turn left
void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight)
{
	SETBIT(PORTD, PORTD6);
	CLEARBIT(PORTE, PORTE6);
	TMR4_PWM_Phase_Duty(255 - speedLeft, speedRight);
}