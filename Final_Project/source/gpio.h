/*
 * gpio.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdio.h>
#include <MKL25z4.h>


#define SWITCH (7)
#define RESET (0)
#define SET (1)

extern int Flag_Interrupt;

/*
 *  This function initializes the PD7 Pin and use that as an interrupt.
 */
void Init_GPIO();

/*
 * after the pushbutton is pressed, the iNT_FLAG is set
 */
void PORTD_IRQHandler();

#endif /* GPIO_H_ */
