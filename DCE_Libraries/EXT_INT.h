#ifndef EXT_INT_H_
#define EXT_INT_H_

#include <avr/io.h>

#define LOW_LEVEL 0 // It is the decimal value equivalent to ICS01=0 and ICS00=0
#define CHANGE 1 // It is the decimal value equivalent to ICS01=0 and ICS00=1
#define FALLING 2 // It is the decimal value equivalent to ICS01=1 and ICS00=0
#define RISING 3 // It is the decimal value equivalent to ICS01=1 and ICS00=1

/// -------------- INLINE FUNCTIONS ----------------
inline static void INT0_config(uint8_t typeTrigger) { EICRA &= 11111100; EICRA |= typeTrigger; }
inline static void INT0_enable() { EIMSK |= (1 << INT0); }
inline static void INT0_disable() { EIMSK &= ~(1 << INT0); }

inline static void INT1_config(uint8_t typeTrigger) { EICRA &= 11110011; EICRA |= (typeTrigger << 2); }
inline static void INT1_enable() { EIMSK |= (1 << INT1); }
inline static void INT1_disable() { EIMSK &= ~(1 << INT1); }

#endif