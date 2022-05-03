/*
 * init.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */




#include "init.h"



#define SYSTEM_CLOCK_FREQ      48000000UL  // 48 Mhz
#define SYTICK_TIME_INTERVAL   1           // 1 msec
#define SYTICK_TIME_FREQ       (SYTICK_TIME_INTERVAL * 1000) // 1000 Khz
#define SYSTICK_TMR_RELOAD_VAL ((SYSTEM_CLOCK_FREQ / SYTICK_TIME_FREQ) - 1UL) // 48000 - 1


static void config_sys_clock(void);
static void SysTickConfig(void);
static void lcd_init(void);


void system_init(void)
{
	// Disable all global interrupts
	__disable_irq();

	// Configure System Clock
	config_sys_clock();

	// Initialize system tick timer
	SysTickConfig();

	// Initialize the LCD
	lcd_init();

	// Init ADC
	init_ADC();

	// Enable all global interrupts
	__enable_irq();
}


/*
 *  For documentation please visit- init.h
 */

static void config_sys_clock(void)
{
	MCG->C1 |= MCG_C1_CLKS(0);  // Select PLL/FLL as clock source

	// MCG_C1: IREFS (bit 2)  = 1
	MCG->C1 |= MCG_C1_IREFS(1); // Select Inernal Reference clock
	                            // source for FLL

	// MCG_C4: DRST_DRS (bit 6-5) = 01
	MCG->C4 |= MCG_C4_DRST_DRS(1); // Select DCO range as Mid range
	                               // DCO generates the FLL Clock

	// MCG_C4: DMX32 (bit 7) = 1
	MCG->C4 |= MCG_C4_DMX32(1);    // Select DCO frequency as 48Mhz
}


/*
 * For documentation please visit- init.h
 */

static void SysTickConfig(void)
{
  SysTick->LOAD  = (uint32_t)(SYSTICK_TMR_RELOAD_VAL);  /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                 /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;             /* Enable SysTick IRQ and SysTick Timer */
}


/*
 * For documentation please visit- init.h
 */

static void lcd_init(void)
{


	// Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	// Enable all LCD pins as GPIO
	PORTC_PCR10 |= PORT_PCR_MUX(1); // PTC10
	PORTC_PCR7 |= PORT_PCR_MUX(1); // PTC7
	PORTC_PCR6 |= PORT_PCR_MUX(1); // PTC6
	PORTC_PCR5 |= PORT_PCR_MUX(1); // PTC5
	PORTC_PCR4 |= PORT_PCR_MUX(1); // PTC4
	PORTC_PCR3 |= PORT_PCR_MUX(1); // PTC3
	PORTC_PCR0 |= PORT_PCR_MUX(1); // PTC0

	// Configure all pins as output.
	GPIOC->PDDR |= (LCD_DB7 | LCD_DB6 | LCD_DB5 | LCD_DB4 |
	                LCD_E   | LCD_RS  | LCD_RW);
}
