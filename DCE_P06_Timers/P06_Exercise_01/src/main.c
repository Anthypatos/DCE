/**
	@file		Juan de la Cruz Caravaca Guerrero
	@date		04/05/2022
    @brief		500ms - Hardware timer 
    @par		Description 
				Uses the 16-bit Timer1 to make the Arduino built-in LED blink. (1Hz)
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../../DCE_Libraries/TMR1.h"
#include "../../../DCE_Libraries/EXT_INT.h"
#include "../../../DCE_Libraries/MACROS.h"
#include "../../../DCE_Libraries/ADC.h"
#include "PORTS.h"


static volatile uint16_t reading = 0;

// ===================		ISR          ===============================================
ISR(TIMER1_COMPA_vect)
{
	ADC_enaInterrupt();
	ADC_Read(ADC0);
}

ISR(ADC_vect)
{
	reading = ADC;
	ADC_disableInterrupt();
}


/// ===================	MAIN FUNCTION    =================================================
int main(void)
{
	///-------------		Setup			-------------------------------------------------------
	/// 1.- Config ports
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	
	/// 2.- Configure TMR1 as CTC with interrupts
	TMR1_CTC_Init();
	TMR1_CTC_EnaInterrupt();
	TMR1_HW_toggleOC1A();	// Connect the oscilloscope to this port
	
	/// 3.- Set the matching value to reach 500ms (@Pre-scaler 1024)
	TMR1_CTC_Set(7813);
	
	/// 4.- Set the pre-scaler and start the timer
	TMR1_CTC_Start(DIV_CLK_1024);
	
	sei();
	
	/// -------------		Super-Loop      -----------------------------------
	while (1)
	{
		if (reading > 512) SETBIT(GPIO_B_OUT, LED0_PIN);
		else CLEARBIT(GPIO_B_OUT, LED0_PIN);
	}
}