/*
 * roll_pitch.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */
#include <roll_pitch.h>



#define OFFSET_ANGLE (90)


/*
 * For documentaion please visit stabilizer.h
 */
void Roll_Detector( )
{
	int roll_polarity=0;
	int roll_percentage;


	if( roll > 0)
		roll_polarity = 1;   //Notes the Roll Polarity

	//computing Roll percentage(fraction to reflect it as LED brightness
	roll_percentage = ((fabs(roll))/ OFFSET_ANGLE)*PWM_PERIOD;

	//Applies the roll on the LED
	Roll_Controller(roll_percentage, roll_polarity );

}


/*
 *  For documention please visit stabilizer.h
 */
void Roll_Controller( int Roll, int Polarity)
{
	if(Polarity)
		Write_LED( Roll, 0, 0);  //positive roll shown using RED LED
	else
		Write_LED(0, 0, Roll ); //negative roll shown using BLUE LED

}


/*
 * For documention please visit stabilizer.h
 */
void Pitch_Detector( )
{
	int pitch_polarity=0;
	int pitch_percentage;


	if( pitch > 0)
		pitch_polarity = 1;     //Notes pitch polarity

	//computes pitch percentage of PWM period
	pitch_percentage = ((fabs(pitch))/ OFFSET_ANGLE)*PWM_PERIOD;

	Pitch_Controller(pitch_percentage, pitch_polarity );

}


/*
 *  For documention please visit stabilizer.h
 */
void Pitch_Controller( int Pitch, int Polarity)
{
	if(Polarity)
		Write_LED( 0, Pitch, 0);
	else
		Write_LED(Pitch, Pitch, Pitch );

}
