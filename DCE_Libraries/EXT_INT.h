/**
	@file		EXT_INT.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		13/04/2022
    @brief		Header file used to toggle interrupts.
*/

#ifndef EXT_INT_H_
#define EXT_INT_H_

#include <avr/io.h>
#include <stdint.h>
#include "MACROS.h"

#define LOW_LEVEL	0 // It is the decimal value equivalent to ICS01=0 and ICS00=0
#define CHANGE		1 // It is the decimal value equivalent to ICS01=0 and ICS00=1
#define FALLING		2 // It is the decimal value equivalent to ICS01=1 and ICS00=0
#define RISING		3 // It is the decimal value equivalent to ICS01=1 and ICS00=1

/// -------------- INLINE FUNCTIONS ----------------
// INT0
static inline void INT0_config(uint8_t typeTrigger) { EICRA &= 11111100; EICRA |= typeTrigger; }
static inline void INT0_enable() { SETBIT(EIMSK, INT0); }
static inline void INT0_disable() { CLEARBIT(EIMSK, INT0); }

// INT1
static inline void INT1_config(uint8_t typeTrigger) { EICRA &= 11110011; EICRA |= (typeTrigger << 2); }
static inline void INT1_enable() { SETBIT(EIMSK, INT1); }
static inline void INT1_disable() { CLEARBIT(EIMSK, INT1); }

// PCINT0
static inline void PCINT0_enable() { SETBIT(PCICR, PCIE0); }
static inline void PCINT0_disable() { CLEARBIT(PCICR, PCIE0); }
static inline void PCINT0_enableBit(uint8_t pin) { SETBIT(PCMSK0, pin); }
static inline void PCINT0_disableBit(uint8_t pin) { CLEARBIT(PCMSK0, pin); }

// PCINT1
static inline void PCINT1_enable() { SETBIT(PCICR, PCIE1); }
static inline void PCINT1_disable() { CLEARBIT(PCICR, PCIE1); }
static inline void PCINT1_enableBit(uint8_t pin) { SETBIT(PCMSK1, pin); }
static inline void PCINT1_disableBit(uint8_t pin) { CLEARBIT(PCMSK1, pin); }

// PCINT2
static inline void PCINT2_enable() { SETBIT(PCICR, PCIE2); }
static inline void PCINT2_disable() { CLEARBIT(PCICR, PCIE2); }
static inline void PCINT2_enableBit(uint8_t pin) { SETBIT(PCMSK2, pin); }
static inline void PCINT2_disableBit(uint8_t pin) { CLEARBIT(PCMSK2, pin); }

// USART0
static inline void USART0_enaInterrupt_RX() { SETBIT(UCSR0B, RXCIE0); }
static inline void USART0_disableInterrupt_RX() { CLEARBIT(UCSR0B, RXCIE0); }
static inline void USART0_enaInterrupt_TX() { SETBIT(UCSR0B, UDRIE0); }
static inline void USART0_disableInterrupt_TX() { CLEARBIT(UCSR0B, UDRIE0); }

// ADC
static inline void ADC_enaInterrupt() { SETBIT(ADCSRA, ADIE); }
static inline void ADC_disableInterrupt() { CLEARBIT(ADCSRA, ADIE); }

// TIMER1
static inline void TMR1_CTC_EnaInterrupt() { SETBIT(TIMSK1, OCIE1A); }	// Enables interrupt on compare match
static inline void TMR1_CTC_DisInterrupt() { CLEARBIT(TIMSK1, OCIE1A); } // Disables interrupt on compare match

#endif