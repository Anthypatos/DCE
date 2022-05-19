/**
	@file		MACROS.h
	@author		Mirian Cifredo
	@date		27/02/2022
    @brief		Header file describing macros for AVR C.

*/


#ifndef MACROS_H_
#define MACROS_H_

//***********************************************/
/* MACROS DEFINE */
/* (AVR035: Efficient C Coding for AVR) */
/***********************************************/

// Set and clear bits in I/O registers declared as macros 
#define SETBIT(ADDRESS, BIT) 		(ADDRESS |= (1 << BIT))
#define CLEARBIT(ADDRESS, BIT) 		(ADDRESS &= ~(1 << BIT))

// Macro for testing of a single bit in an I/O location
// Return 0 (false) while the flag is not asserted
#define CHECKBIT(ADDRESS, BIT) 		(ADDRESS & (1 << BIT))

#define TOGGLEBIT(ADDRESS, BIT) 		(ADDRESS ^= (1 << BIT))
//------------------------------------------------------

#define	IS_PIN_ZERO(ADDRESS,BIT)	!(ADDRESS & (1 << BIT))	// Flag=0 --> TRUE
#define	READ_PIN(ADDRESS,BIT)		(ADDRESS & (1 << BIT))	// Read a pin (Same as CHECKBIT)

#define READ_TRUE 			1
#define READ_FALSE 			0
//------------------------------------------------------

/// Time in ms the MCU waits for the bouncing in the pushbutton.
#define DEBOUNCE_TIME	100		

/// Time in ms the LED stays ON or OFF.
#define BLINK_TIME 500

#endif /* MACROS_H_ */