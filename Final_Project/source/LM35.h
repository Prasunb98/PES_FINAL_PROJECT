/*
 * LM35.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef LM35_H_
#define LM35_H_

#include "mkl25z4.h"
#include "adc.h"
#include "lcd.h"
#include <stdio.h>
#include <stdint.h>

/*
 * This function calls the adc_read function and gets the analog value from ADC015 pin
 * after getting the value the conversion is done using the formula;
 * Then  sending the value to dispaly on the LCD.
 *
 * T = (((3.0 * ADC_reading) /1024)/ 1000)/10
 * which is equivalent to; T = (adc_reading *300)/1024
 *
 */
void scan_temperature(void);

#endif /* LM35_H_ */
