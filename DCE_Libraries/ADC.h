/**
	@file		ADC.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		19/04/2022
    @brief		Header file including macros to configure the ADC.
    @par		Description 
				The configuration can be modified by changing the macros.
				For other MCU only this header file will need to be modified.
*/


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <avr/io.h>

// Parameters related to ADC -----------------------------------
#define AREF		0
#define AVCC		1

#define ALIGN_RIGHT	0
#define ALIGN_LEFT	1

#define ADC0		0
#define ADC1		1
#define ADC2		2
#define ADC3		3
#define ADC4		4
#define ADC5		5
#define ADC6		6
#define ADC7		7
#define ADC8		8
#define ADC9		9
#define ADC10		10

#define SAMPLE1		1
#define SAMPLE2		2
#define SAMPLE4		4
#define SAMPLE8		8
#define SAMPLE16	16

//--------------- PROTOTYPES ---------------------------------------
uint16_t ADC_Read_Single_Poll(uint8_t channel);
void ADC_Read();


//---------------- FUNCTIONS -----------------------------------------

static inline void ADC_Init_Single(uint8_t vref, uint8_t alignment)	
{
	//  0.- Delete a previous configuration
    ADMUX = ADCSRA = 0x00;

	//  1.- Select Vref: AVcc --> (REFS1-0 = "01")	Aref --> (REFS1-0 = "00")
	ADMUX |= (vref << REFS0);
	
	//	2.- Select the aligment format for ADC register (10-bits): 
	//			--> ALIGN_LEFT --> (ADLAR=1)  --> ALIGN_RIGHT --> (ADLAR=0)
	ADMUX |= (alignment << ADLAR);

	//  3.- Set pre-scaler  -->  Prescaler 16MHZ/128 = 125 KHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	//  4.- Enable ADC (ADEN = '1')
	// 	(It could be an separated function if disabling the ADC is desirable)
	ADCSRA |= (1 << ADEN);
	
	//  5.- Single Mode 
	// 	(It could be an separated function if changing the ADC mode is desirable)
	ADCSRA &= ~(1 << ADATE);
}

#endif /* ADC_H_ */