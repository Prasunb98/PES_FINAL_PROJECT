/*
 * pwm.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define	PWM_PERIOD	(4800)

/*
 * This function initialize PWM for BLUE, RED and GREEN LED
 */
void PWM_Init();

/*
 * This function controls the strength of the PWM signal for three LEDs
 *
 *  @ Parameters: Takes the PWM input for red, blue and GREEN
 *
 */
void Write_LED( int Red, int Green, int Blue);



#endif /* PWM_H_ */
