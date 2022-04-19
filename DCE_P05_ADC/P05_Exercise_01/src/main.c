#include <avr/io.h>
#include <stdint.h>
#include "../../../DCE_Libraries/ADC.h"
#include "../../../DCE_Libraries/USART.h"
#include "../../../DCE_Libraries/MACROS.h"
#include "PORTS.h"

int main()
{
	GPIO_config();
	ADC_Init_Single(AVCC, ALIGN_RIGHT);
	
	uint16_t reading = 0;
	
	while(1)
	{
		reading = ADC_Read_Single_Poll(ADC1);
		
		if (reading <= 255) GPIO_B_OUT = (1 << LED0_PIN);
		else if (reading <= 512) GPIO_B_OUT = (1 << LED1_PIN);
		else if (reading <= 768) GPIO_B_OUT = (1 << LED2_PIN);
		else GPIO_B_OUT = (1 << LED3_PIN);
	}
}