/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		18/05/2022
    @brief		Mobile robot
    @par		Description 
				This program runs a test of the robot's buzzer and wheels.
*/

#define F_CPU		16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TMR0.h"
#include "TMR1.h"
#include "TMR4.h"
#include "TEST_BUZZER.h"
#include "EXT_INT.h"
#include "WHEELS.h"

//-------------------------------- DEFINITIONS --------------------------
typedef enum
{
	STATE_INIT,		// Beeps once
	STATE_TEST,		// Runs test of the wheels
	STATE_STOP		// Beeps thrice
} State_t;

//--------------------------- GLOBAL PARAMETERS ----------------------------
static volatile State_t state = STATE_INIT;

//-------------------------------- PROTOTYPES -------------------------------
static inline void Robot_Test();

//---------------------------------- ISR -----------------------------------
ISR(TIMER0_COMPA_vect) { playSound(STARTING_SOUND); }


ISR(TIMER1_COMPA_vect)
{
	TMR0_CTC_Stop();
	TMR1_CTC_Stop();
}


//----------------------------------------- MAIN ----------------------------
int main(void)
{
	// Setup
	TMR0_CTC_Init();
	TMR0_CTC_Set(32);		// aka 2ms
	TMR1_CTC_Init();
	TMR1_CTC_Set(7813);		// aka 0.5s
	
	sei();
	TMR0_CTC_EnaInterrupt();
	TMR1_CTC_EnaInterrupt();
	
	setupWheels();
	TMR4_PWM_Phase_Start(TMR4_DIV_CLK_64);
	Robot_STOP();
	
	//---------------------------------- Superloop --------------------------
    while (1) 
    {
		switch (state)	// See above
		{
			case STATE_INIT:	
				TMR0_CTC_Start(DIV_CLK_1024);
				TMR1_CTC_Start(DIV_CLK_1024);
				_delay_ms(1000);
				
				state = STATE_TEST;
				break;
			case STATE_TEST:
				Robot_Test();
				
				state = STATE_STOP;
				break;
			case STATE_STOP:
				_delay_ms(3000);
				
				for (uint8_t i = 0; i < 3; i++)
				{
					TMR0_CTC_Start(DIV_CLK_1024);
					TMR1_CTC_Start(DIV_CLK_1024);
					_delay_ms(1000);
				}
				_delay_ms(1000);
				
				state = STATE_INIT;
				break;
		}
    }
}


// Tests each of the possible types of movement for the wheels
static inline void Robot_Test()
{
	_delay_ms(1000);
	Robot_FWD(36, 36);
	_delay_ms(1000);
	Robot_BWD(36, 36);
	_delay_ms(1000);
	Robot_LEFT(36, 36);
	_delay_ms(1000);
	Robot_RIGHT(36, 36);
	_delay_ms(1000);
	Robot_STOP();
}