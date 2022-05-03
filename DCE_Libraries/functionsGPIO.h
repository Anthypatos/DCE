/**
	@file		functionsGPIO.h
	@author		Juan de la Cruz Caravaca Guerrero
	@date		11/04/2022
    @brief		Header file including functions to configure the GPIOs.
*/

#ifndef FUNCTIONS_GPIO_H_
#define FUNCTIONS_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

bool read_input(uint8_t portGPIO, uint8_t pinNumber);

#endif