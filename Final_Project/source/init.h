/*
 * init.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */
#include <stdint.h>
#include "mkl25z4.h"
#include "lcd.h"
#include "adc.h"

#ifndef INIT_H_
#define INIT_H_

// LCD Pins namings
#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10


/*
 * Putting it in critical section
 * by disabling the interrupt, initializing LCD and ADC and then
 * disabling the interrupt as well.
 *
 */

void system_init(void);



#endif /* INIT_H_ */
