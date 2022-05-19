/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		10/05/2022
    @brief		Color-detection robot
    @par		Description 
				This logic makes the robot detect colors on its IR0 and play
				a correspondent sound. The color can change at any time and
				the sound will be switched instantaneously.
*/

#define F_CPU		16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "OPTO_SENSORS.h"
#include "EXT_INT.h"
#include "TEST_BUZZER.h"
#include "TMR0.h"
#include "TMR1.h"
#include "m_general.h"
#include "m_usb.h"


static volatile uint8_t iStart = 0;		// Number of times the starting sound has been played
static volatile bool bSound = false;	// Marks if a sound must be played inside the timer's ISR
static volatile uint16_t reading = 0;	// Reading for the IR0

// -------------------------------- ISR ------------------------------------
ISR(TIMER0_COMPA_vect) 
{
	if (iStart < 3) playSound(STARTING_SOUND); // Have we played the starting sound thrice?
	else
	{
		// Reads the IR0. The reason why this is not inside the ADC's routine is because the
		// TIMER0's ISR has a higher priority. Doing it this way allows us to quickly switch the
		// sound without having to wait for the completion of the previous playback.
		if ((reading < 500 && ADC >= 500) || (reading >= 500 && ADC < 500)) // Has the color changed?
		{
			reading = ADC;
			bSound = true;					// If so, we can play a new sound
			TMR0_CTC_Start(DIV_CLK_1024);	// So we reset both timers
			TMR1_CTC_Start(DIV_CLK_1024);
		}
		
		if (bSound)	// Do we need to play a sound?
		{
			if (reading < 500) playSound(MATCH_SOUND);
			else playSound(FAIL_SOUND);
		}
	}
}


ISR(TIMER1_COMPA_vect)
{
	if (iStart < 3) // Have we played the starting sound thrice?
	{
		iStart++;
		_delay_ms(500);	// Waiting for a little bit, we only need to do it thrice
		TMR0_CTC_Start(DIV_CLK_1024);	// Reset the timers so we don't lose time for the next run
		TMR1_CTC_Start(DIV_CLK_1024);
		
		if (iStart == 3) TMR1_CTC_Stop();	// We don't need to play this thing anymore
	}
	else
	{
		bSound = false;	// The whole length of the sound has been played, we stop
		TMR1_CTC_Stop();
	}
}


//----------------------------------- MAIN -------------------------------------
int main()
{
	// Setup
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	TMR0_CTC_Init();
	TMR0_CTC_Set(32);		// aka 2ms
	TMR1_CTC_Init();
	TMR1_CTC_Set(15625);	// aka 1s
	
	check_IR_Sensor(IR0);	// First reading is slower
	
	sei();
	TMR0_CTC_EnaInterrupt();
	TMR1_CTC_EnaInterrupt();
	
	TMR0_CTC_Start(DIV_CLK_1024);
	TMR1_CTC_Start(DIV_CLK_1024);
	
	//--------------------------------- Superloop ------------------------------------
	while(1) check_IR_Sensor(IR0);	// Performs a conversion
}
