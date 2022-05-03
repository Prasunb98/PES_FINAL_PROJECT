/*
 * systick.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

#include "mkl25z4.h"
#include <stdint.h>
#include "lcd.h"

extern volatile uint8_t flag_50msec;
extern volatile uint8_t flag_100msec;
extern volatile uint8_t flag_500msec;
extern volatile uint8_t flag_1sec;

/*
 * This function generates software based time delay
 *
 */

void SysTick_Handler(void);

#endif /* SYSTICK_H_ */
