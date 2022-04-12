#define  F_CPU	16000000UL
#include <avr/io.h>	 			
#include <util/delay.h>
#include <stdio.h>
#include "../../../DCE_Libraries/USART.h"

inline static void mainMenu();

int main(){
	
	USART0_Init(UBRR_VALUE);
	mainMenu();
	char key = ' ';
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1)	
    {	
		if (UCSR0A & (1 << RXC0))
		{
			key = UDR0;
			
			// 2. Answer to the choice selected
			switch (key)
			{
				case 'a':
					USART0_putString("You pressed 'a'.\n\r");
					break;
				case 'b':
					USART0_putString("You pressed 'b'.\n\r");
					break;
				case 'h':
				case 'H':
					mainMenu();
					break;
				default:
					USART0_putString("I don't know what to do with that key");
					break;
			}
		}
	}
}

inline static void mainMenu()
{
	USART0_putString("\f----------------------------------------\n\r"
					"This is the main menu. Select one choice:\n\r"
					"----------------------------------------\n\r"
					"a. Choice 'a'\n\r"
					"b. Choice 'b'\n\r"
					"\n\r"
					"h. Show the menu again\n\r"
					"----------------------------------------\n\r");
}