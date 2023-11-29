/*
 ============================================================================
 Name        : calculator.c
 Author      : Tarek Ahmed
 Description : Simple Calculator
 ============================================================================
 */

#include "../HAL/calc.h"
int main(void)
{


	start(); //Start interface

	for(;;)
	{
		Do_Caclulations();//Start program (Calculations)
	}


}


