#ifndef FUNCTIONS_GPIO_H_
#define FUNCTIONS_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

bool read_input(uint8_t portGPIO, uint8_t pinNumber);

#endif