/*
 * pwm.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */


#include "PWM.h"

#define BLUE_LED_POS   (1)
#define	RED_LED_POS	   (18)
#define	GREEN_LED_POS  (19)

static void BLUE_PWM(uint16_t period);
static void RED_PWM(uint16_t period);
static void GREEN_PWM(uint16_t period);

/*
 * For documentation please visit- pwm.h
 */

void PWM_Init()
{
	BLUE_PWM(PWM_PERIOD);
	RED_PWM(PWM_PERIOD);
	GREEN_PWM(PWM_PERIOD);
}

/*
* For documentation please visit - pwm.h
*/

void BLUE_PWM(uint16_t period)
{
	//Enable clock to PORTD, TPM0
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Set pin to FTM
	//Blue FTM0_CH1, Mux Alt4
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);

	//Configure TPM
	//Set clock source for TPM: 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Load the counter and mod. Indicates upper threshold value
	TPM0->MOD = period -1;

	//Set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC = TPM_SC_PS(1);

	//Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);

	//Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	//Set initial duty cycle
	TPM0->CONTROLS[1].CnV = 0;

	//Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}

/*
 *  FOR DOCUMENATION PLEASE VISIT - pwm.h
 */

static void RED_PWM(uint16_t period)
{
	//Enable clock to PORTB, TPM2
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//Set pin to FTM
	//Red FTM2_CH0, Mux Alt3
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);

	//Configure TPM
	//Set clock source for TPM: 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Load the counter and mod. Indicates upper threshold value
	TPM2->MOD = period -1;

	//Set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC = TPM_SC_PS(1);

	//Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	//Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	//Set initial duty cycle
	TPM2->CONTROLS[0].CnV = 0;

	//Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);

}

/*
 *
 *  FOR DOCUMENATION PLEASE VISIT - pwm.h
 *
 */

static void GREEN_PWM(uint16_t period)
{
	//Enable clock to PORTB, TPM2
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//Set pin to FTM
	//Red FTM2_CH1, Mux Alt3
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);

	//Configure TPM
	//Set clock source for TPM: 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Load the counter and mod. Indicates upper threshold value
	TPM2->MOD = period -1;

	//Set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC = TPM_SC_PS(1);

	//Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	//Set channel 1 to edge-aligned low-true PWM
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	//Set initial duty cycle
	TPM2->CONTROLS[1].CnV = 0;

	//Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

/*
 *   FOR DOCUMENATION PLEASE VISIT - pwm.h
 */
void Write_LED( int Red, int Green, int Blue)
{
	TPM2->CONTROLS[0].CnV = ((Red) );
	TPM2->CONTROLS[1].CnV = ((Green));
	TPM0->CONTROLS[1].CnV = ((Blue));

}

