/*
 * led.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */



#include "led.h"

//Universal Mask to access LED pins
#define MASK(x) (1UL << (x))


/*
 *  For documentation please visit- led.h
 */
void RGB_INIT(void) {
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;;

	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);

	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
}

/*
 *  For documentation please visit- led.h
 */
void Control_RGB_LEDs(unsigned int RED, unsigned int GREEN, unsigned int BLUE)
{
	if (RED)
		PTB->PCOR = MASK(RED_LED_POS);
	else
		PTB->PSOR = MASK(RED_LED_POS);
	if (GREEN)
		PTB->PCOR = MASK(GREEN_LED_POS);
	else
	    PTB->PSOR = MASK(GREEN_LED_POS);
	if (BLUE)
		PTD->PCOR = MASK(BLUE_LED_POS);
	else
	    PTD->PSOR = MASK(BLUE_LED_POS);
}




