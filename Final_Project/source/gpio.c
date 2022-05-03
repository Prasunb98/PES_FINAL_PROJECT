/*
 * gpio.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 *      This function initialize the GPIO and interrupt part
 */


#include "gpio.h"


int Flag_Interrupt;

/*
 * For documentation please visit- gpio.h
 */
void Init_GPIO()
{
	SIM ->SCGC5 |= SIM_SCGC5_PORTD_MASK;           // Sourcing clock to port D
	PORTD->PCR[SWITCH] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[SWITCH] |= PORT_PCR_MUX(1);     // multiplexing the pin to GPIO
	PORTD->PCR[SWITCH] |= PORT_PCR_IRQC(10);   // Setting the configuration to falling edge
	PORTD->PCR[SWITCH] |= PORT_PCR_PE_MASK;    // Enabling pull up resistor configuration
	PORTD->PCR[SWITCH] |= PORT_PCR_ISF_MASK;   // Setting the interrupt flag
	PORTD->PCR[SWITCH] |= PORT_PCR_PS_MASK;    // Enabling Pull select

	NVIC_EnableIRQ(PORTD_IRQn);

}

/*
 * For documentation please visit- gpio.h
 */
void PORTD_IRQHandler()
{
	NVIC_DisableIRQ(PORTD_IRQn);
	Flag_Interrupt=SET;
	PORTD->PCR[SWITCH] |= PORT_PCR_ISF_MASK;
	NVIC_EnableIRQ(PORTD_IRQn);

}
