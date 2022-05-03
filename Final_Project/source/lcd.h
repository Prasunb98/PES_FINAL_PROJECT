/*
 * lcd.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "fsl_debug_console.h"
#include <stdint.h>
#include <string.h>
#include "mkl25z4.h"
#include "init.h"
#include <stdio.h>
#include <math.h>

/*
 * This function initialize the respective command for LCD
 *
 */
void start_lcd(void);
/*
 * This function do the respective functionalities for writing a character string to LCD.
 * Param - string to write
 */

uint8_t lcd_string_write(char *str);

/*
 * This function helps to write temperature data on LCD
 * Param- temperature input data to display
 */
void display_temperature(uint8_t temp);

/*
 * This function helps to write Roll Angle data on LCD
 * Param - Input roll data to display
 */
void display_roll(uint8_t input_roll);

/*
 * This function helps to write Pitch Angle data on LCD
 * Param - Input pitch angle data to display
 */
void display_pitch(uint8_t input_pitch);

#endif /* LCD_H_ */
