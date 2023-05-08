/******************************************************************************
 *
 * File Name: calc.h
 *
 * Description: Header file for the calculator driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef CALC_H_
#define CALC_H_

/*******************************************************************************
 *                       Includes                                           *
 *******************************************************************************/
#include "../mcu_config/std_types.h"




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * Start Application with displaying welcome and wait to  enter c
 */
void start(void);


void Do_Caclulations(void);


void Random(void);



#endif /* CALC_H_ */
