#include <avr/interrupt.h>
#include "../../../DCE_Libraries/TMR1.h"
#include "../../../DCE_Libraries/EXT_INT.h"
#include "../../../DCE_Libraries/MACROS.h"
#include "PORTS.h"

ISR(TIMER1_COMPA_vect)
{
	TOGGLE(GPIO_B_OUT, LED0_PIN);
}


int main()
{
	GPIO_config();
	
	TMR1_CTC_Init();
	
	TMR1_CTC_EnaInterrupt();
	sei();
	
	TMR1_CTC_Set(500 / 64 * 1000);
	TMR1_CTC_Start(DIV_CLK_1024);
	
	while (1);
}