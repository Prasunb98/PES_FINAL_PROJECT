/*
 * calibrate.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef CALIBRATE_H_
#define CALIBRATE_H_

#include "gpio.h"
#include "mma8451Q.h"
#include <MKL25Z4.H>
#include "i2c.h"
#include "fsl_debug_console.h"
#include <stdint.h>

/*
 * This function helps in calibrating the accelerometer using single offset calibration method
 * This is same as the method mentioned in AN4069, it takes the reading of the sensor at the position when the
 * pushbutton is pressed and it calculates the offset.
 */

void accel_calibrate();


/*
 *  This Function takes the repeated reading of acceleration values and put it down to
 *  the pointer
 *
 */
void Read_ACCxyz( int16_t * acc_values);

#endif /* CALIBRATE_H_ */
