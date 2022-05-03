/*
 * LM35.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#include "LM35.h"

/*
 *
 * Putting the adc pin on ADC0_15 for temp_valueerature sensor
 */

#define TEMPERATURE_SENSOR_CHN   (15)

/* Writing 31 to dispable ADC */
#define DISABLE_ADC  (31)

/* ADC Vref voltage (3.0v) in multiplication of 100th
*/
#define VREF_FACTOR (300)


/*
 *
 * For documentation please visit - LM35.h
 */

void scan_temperature(void)
{
	static uint16_t adc_output;
	static uint16_t adc_output_avg;
	static uint16_t temp_value;
	static uint8_t counter;

	/* Increments every 1 second */
	counter++;

	/* Get ADC Result for temp_valueerature sensor */
	adc_output += adc_read(TEMPERATURE_SENSOR_CHN);

	/* Take 16 samples to calculate temp_value */
	if (counter >= 16)
	{
		adc_output_avg = adc_output >> 4;       /* Get ADC average value */

		/* According to this formulae ; T = (adc_reading * 3 * 100) / 1024 */

		temp_value = ((adc_output_avg * VREF_FACTOR) >> 10);


		adc_output = 0;
		counter = 0;
	}

	/* Display temp_valueerature */
	display_temperature(temp_value);



	/* Disable ADC module */
	ADC0_SC1A |= ADC_SC1_ADCH(DISABLE_ADC);
}
