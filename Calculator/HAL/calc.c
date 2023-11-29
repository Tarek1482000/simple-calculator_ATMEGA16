/******************************************************************************
 *
 * File Name: calc.c
 *
 * Description: Source file for the calculator driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/


#include "calc.h"
#include "lcd.h"
#include "keypad.h"
#include "../MCAL/ex_interrupt.h"
#include "../mcu_config/private.h"
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

uint8   key=0,   //Store Keypad value
num1_counter=0,  //number1 counter store digits
num2_counter=0,  //number2 counter store digits
opration=0,      //Store operation type
random_num = 1;

float32 number1[10]={0}, //First Number
		number2[10]={0}, //Second NumberS
		result=0;        //Calculation Result


/*
 * Description :
 * Initialize the LCD:
 * Start Application with displaying welcome and wait to  enter c
 */
void start(void)
{
	Ex_INT_ConfigType Config_Ptr =
	{
			EX_INT0,FALLING_EDGE,NORMAL_EX_INT_PIN
	};
	Ex_INT_init(&Config_Ptr);
	INT0_setCallBack(Random);
	sei()

	LCD_init();
	LCD_displayStringRowColumn(0,4,"Hello Sir");
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}





/*
 * Description :
 * Get the first number and operation of calculation
 */
void First_NUM(void)
{

	uint8 temp = 0;
	num1_counter=0;//start from digit 1
	while(1)
	{

		key=KEYPAD_getPressedKey();
		_delay_ms(200);

		if(random_num == 0)
		{
			random_num = 1;

			key = rand() % 10;
		}


	if( key == '/' )
		{
			temp=KEYPAD_getPressedKey();
			_delay_ms(200);
		}

		if(temp == '/' )
		{
			key = 'R';
		}


		/*
		 * Break loop when user complete entering first number and operation
		 */
		if(key == '+' || key == '-' || key == '/' || key == '*')
		{
			opration=key;
			LCD_displayCharacter(opration);
			break;
		}

		if( key == 'R')
		{
			opration=key;
			LCD_displayString("Root");
			break;
		}
		/*
		 * Store all digits of first number and display number on LCD
		 */
		number1[num1_counter]=key;
		num1_counter++;
		LCD_intgerToString(key);
	}
}


/*
 * Description :
 * Get the first number and operation of calculation
 */
void Second_NUM(void)
{
	num2_counter=0;
	while(1)
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);

		if(random_num == 0)
		{
			random_num = 1;

			key = rand() % 10;
		}


		/*
		 * Break loop when user complete entering second number
		 */
		if(key == '=')
		{
			LCD_displayCharacter(key);
			break;
		}


		/*
		 * Store all digits of second number and display number on LCD
		 */
		number2[num2_counter]=key;
		num2_counter++;
		LCD_intgerToString(key);
	}
}




/*
 * Description :
 * Concatenate all digits of two number then display result of sum on LCD
 */
void calc_sum(float32 *first_num,float32*second_num,uint8 digit1,uint8 digit2)
{
	float32 num1=first_num[0];
	float32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(uint8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(uint8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_intgerToString(num1+num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}


/*
 * Description :
 * Concatenate all digits of two number then display result of sub on LCD
 */
void calc_sub(float32 *first_num,float32*second_num,uint8 digit1,uint8 digit2)
{
	uint16 num1=first_num[0];
	uint16 num2=second_num[0];
	/*
	 *  Concatenate all digits of first number
	 */
	for(uint8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(uint8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1,0);
	LCD_intgerToString(num1-num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}


/*
 * Description :
 * Concatenate all digits of two number then display result of multi on LCD
 */
void calc_multi(float32 *first_num,float32*second_num,uint8 digit1,uint8 digit2)
{
	float32 num1=first_num[0];
	float32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(uint8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(uint8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_intgerToString(num1*num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}



/*
 * Description :
 * Concatenate all digits of two number then display result of div on LCD
 */
void calc_div(float32 *first_num,float32*second_num,uint8 digit1,uint8 digit2)
{
	float32 num1=first_num[0];
	float32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(uint8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(uint8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_floatToString(num1/num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}

/*
 * Description :
 * Get the root of number then display result of multi on LCD
 */
void calc_ROOT(float32 *first_num,uint8 digit1)
{
	float32 num1=first_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(uint8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */

	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_floatToString(sqrtf(num1));
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(200);
	}
	LCD_clearScreen();
}

/*
 * Description :
 *  Get two number and operation and do operation and display it on screen
 */
void Do_Caclulations(void)
{

	/*
	 * Get first number and operation
	 */
	First_NUM();

		if(opration != 'R')
	{
		/*
		 * Get Second number
		 */
		Second_NUM();
	}


	/*
	 * Do operation calculation
	 */
	switch(opration)
	{
	case '+':
		calc_sum(number1, number2, num1_counter, num2_counter);
		break;
	case '-':
		calc_sub(number1, number2, num1_counter, num2_counter);
		break;
	case '*':
		calc_multi(number1, number2, num1_counter, num2_counter);
		break;
	case '/':
		calc_div(number1, number2, num1_counter, num2_counter);
		break;
	case 'R':
		calc_ROOT(number1, num1_counter);
		break;
	default:
		break;
	}

}

void Random(void)
{
	random_num = 0 ;
}
