/*
 * 	Simple_Calculator.c
 *
 *  Created on: October 5, 2023
 *  Author: Peter Nabil
 */

#include <util\delay.h>
#include "keypad.h"
#include "lcd.h"


int main(void)
{
	uint8 CharacterPressed;
	uint16 firstNumber = 0;
	uint16 secondNumber = 0;
	float32 initialNumber = 0.1;
	uint8 operator;
	uint16 result;
	LCD_init();

	initialNumber = 0.1;
	CharacterPressed = KEYPAD_getPressedKey();
	while((CharacterPressed >= 0) && (CharacterPressed <= 9))
	{
		LCD_intgerToString(CharacterPressed);
		_delay_ms(500);
		initialNumber *= 10;
		firstNumber *= initialNumber;
		firstNumber +=  CharacterPressed;
		CharacterPressed = KEYPAD_getPressedKey();
	}

	while(1)
	{
		if((CharacterPressed == '+') || (CharacterPressed == '-') || (CharacterPressed == '*') || (CharacterPressed == '/'))
		{
			operator = CharacterPressed;
			LCD_displayCharacter(CharacterPressed);
			_delay_ms(500);
		}

		secondNumber = 0;
		initialNumber = 0.1;
		CharacterPressed = KEYPAD_getPressedKey();
		while((CharacterPressed >= 0) && (CharacterPressed <= 9))
		{
			LCD_intgerToString(CharacterPressed);
			_delay_ms(500);
			initialNumber *= 10;
			secondNumber *= initialNumber;
			secondNumber +=  CharacterPressed;
			CharacterPressed = KEYPAD_getPressedKey();
		}

		switch(operator)
		{
		case '+':
			result = firstNumber + secondNumber;
			break;

		case '-':
			result = firstNumber - secondNumber;
			break;

		case '*':
			result = firstNumber * secondNumber;
			break;

		case '/':
			result = firstNumber / secondNumber;
			break;

		}

		if(CharacterPressed == '=')
		{

			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayCharacter('=');
			LCD_intgerToString(result);
			_delay_ms(500);
		}

		firstNumber = result;

		CharacterPressed = KEYPAD_getPressedKey();
		if(CharacterPressed == 13)
		{
			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			firstNumber = 0;
			secondNumber = 0;
			result = 0;

			initialNumber = 0.1;
			CharacterPressed = KEYPAD_getPressedKey();
			while((CharacterPressed >= 0) && (CharacterPressed <= 9))
			{
				LCD_intgerToString(CharacterPressed);
				_delay_ms(500);
				initialNumber *= 10;
				firstNumber *= initialNumber;
				firstNumber +=  CharacterPressed;
				CharacterPressed = KEYPAD_getPressedKey();
			}
		}

	}
	return 0;
}
