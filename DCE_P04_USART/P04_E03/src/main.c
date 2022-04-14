/**
	@file		main.c
	@author		Juan de la Cruz Caravaca Guerrero
	@date		14/04/2022
    @brief		Main menu
    @par		Description
				Shows a menu on the screen and prints different characters.	
*/

#include <avr/io.h>	
#include "../../../DCE_Libraries/USART.h"
#include "../../../DCE_Libraries/MACROS.h"

inline static void mainMenu();

int main(){
	
	USART0_Init(UBRR_VALUE);
	mainMenu();
	char key = ' ';
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1)	
    {	
		if (CHECKBIT(UCSR0A, RXC0))
		{
			key = UDR0;
			
			switch (key)
			{
				case 'a':
					USART0_putString("You pressed a\n\r");
					break;
				case 'b':
					USART0_putString("You pressed b\n\r");
					break;
				case 'h':
					mainMenu();
					break;
				default:
					USART0_putString("I don't know what to do with that key\n\r");
					break;
			}
		}
	}
}

inline static void mainMenu()
{
	USART0_putString("\f-----------------------------------------------\n\r"
					"This is the main menu. Select one choice:\n\r"
					"-----------------------------------------------\n\r"
					"a.- Choice a\n\r"
					"b.- Choice b\n\r"
					"\n\r"
					"h.- Show the menu again\n\r"
					"-----------------------------------------------\n\r");
}