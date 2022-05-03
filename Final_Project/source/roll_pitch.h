/*
 * roll_pitch.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */

#ifndef ROLL_PITCH_H_
#define ROLL_PITCH_H_


#include "mma8451q.h"
#include "led.h"
#include <math.h>
#include "PWM.h"


/*
 *  This function Detects the Roll percentage and its direction
 *
 *
 */
void Roll_Detector( );


/*
 * This function controls the LED brightness based on the PWM strength
 *
 *  Parameter:  takes roll percentage and polarity
 */
void Roll_Controller( int Roll, int Polarity);

/*
 * This function detects the pitch value and conputes its percentage
 *
 */
void Pitch_Detector();

/*
 * @This function control the LED brightness u
 *
 *  Parameter: pitch percentage of PWM along with the polarity
 */
void Pitch_Controller( int Pitch, int Polarity);



#endif /* ROLL_PITCH_H_ */
