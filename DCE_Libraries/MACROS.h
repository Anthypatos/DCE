/**
	@file		MACROS.h
	@author		Mirian Cifredo
	@date		27/02/2022
    @brief		Header file describing macros for AVR C.

*/


#ifndef MACROS_H_
#define MACROS_H_

/********************************************************/
/*			MACROS DEFINE					  		  	*/
/* (AVR035: Efficient C Coding for AVR)		   			*/
/********************************************************/
// Set and clear bits in I/O registers declared as macros 
#define SETBIT(ADDRESS,BIT)		(ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT)	(ADDRESS &= ~(1<<BIT))

// Macro for testing of a single bit in an I/O location
// Return 0 (false) while the flag is not asserted
#define CHECKBIT(ADDRESS,BIT)	(ADDRESS & (1<<BIT))
#define TOGGLE(ADDRESS,BIT)		(ADDRESS ^= (1<<BIT))
//------------------------------------------------------

#define	IS_PIN_ZERO(ADDRESS,BIT)	!(ADDRESS &(1<<BIT))	// Flag=0 --> TRUE
#define	READ_PIN(ADDRESS,BIT)		(ADDRESS &(1<<BIT))		// Check the button state
								
#define BUTTON_PRESSED				0
#define BUTTON_NOT_PRESSED			1


#endif /* PORTS_H_ */