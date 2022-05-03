/*
 * adc.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "MKL25Z4.h"

/*
 *  This function starts the required initialization for single ended mode;
 *   and call the calibration function
 *
 */

void init_ADC(void);


/*
 * Function to do the  conversion and return the analog values till end.
 *
 */

uint16_t adc_read(uint8_t ch);

#endif /* ADC_H_ */
