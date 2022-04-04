#ifndef EXT_INT_H_
#define EXT_INT_H_

#include <avr/io.h>

inline static void INT0_triggerLow() { EICRA &= ~(1 << ISC01) & ~(1 << ISC00); }
inline static void INT0_triggerChange() { EICRA &= ~(1 << ISC01); EICRA |= (1 << ISC00); }
inline static void INT0_triggerFalling() { EICRA |= (1 << ISC01); EICRA &= ~(1 << ISC00); }
inline static void INT0_triggerRising() { EICRA |= (1 << ISC01) | (1 << ISC00); }
inline static void INT0_enable() { EIMSK |= (1 << INT0); }
inline static void INT0_disable() { EIMSK &= ~(1 << INT0); }

inline static void INT1_triggerLow() { EICRA &= ~(1 << ISC11) & ~(1 << ISC10); }
inline static void INT1_triggerChange() { EICRA &= ~(1 << ISC11); EICRA |= (1 << ISC10); }
inline static void INT1_triggerFalling() { EICRA |= (1 << ISC11); EICRA &= ~(1 << ISC10);  }
inline static void INT1_triggerRising() { EICRA |= (1 << ISC11) | (1 << ISC10); }
inline static void INT1_enable() { EIMSK |= (1 << INT1); }
inline static void INT1_disable() { EIMSK &= ~(1 << INT1); }

#endif