/*
 * led.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */
#include <MKL25Z4.H>

#ifndef LED_H_
#define LED_H_

#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D

/*
 *  This function initializes RGB LEDs at respective port and pin.
 *
 */
void RGB_INIT(void);

/*
 *  @This function Turns on depending on different input from the while calling.
 *
 *  Parameters : RED,GREEN,BLUE
 */
void Control_RGB_LEDs(unsigned int RED, unsigned int GREEN, unsigned int BLUE);




#endif /* LED_H_ */
