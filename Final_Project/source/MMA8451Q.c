
/*
 *
 * @ MMA8451Q.c file
 * Created on: Apr 29, 2022
 * @Author - Prasun Biswas
 *
 * This file contains the required elements for initializing, reading X,Y, Z axis
 * and finally updating the X,Y,Z axis value to roll and pitch angle.
 *
 */


#include "mma8451q.h"


#define LOG_TIME (1000)

#define NO_FLOAT (1000)

int16_t acc_X=0, acc_Y=0, acc_Z=0;
int roll=0, pitch=0;

/*
 *
 *  For documentation please visit -mma8451q.h
 *
 */
int init_accel()
{
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*
 *
 *  For documentation please visit -mma8451q.h
 *
 */
void read_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}

	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;

}

/*
 *
 *  For documentation please visit -mma8451q.h
 *
 */
void roll_pitch_calculator(void) {

	//Converting the counts to the actual acceleration values
	int   ax = (acc_X/COUNTS_PER_G)*NO_FLOAT,
		  ay = (acc_Y/COUNTS_PER_G)*NO_FLOAT,
		  az = (acc_Z/COUNTS_PER_G)*NO_FLOAT;

	static int count;

	//calculating ROLL angle using cartesian geometry

	roll = atan2(ay, az)*180/PI;

	//calculating PITCH angle using cartesian geometry
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/PI;

	count++;

	if(count == LOG_TIME)
	{
		count=0;
	    PRINTF( "\n\rCurrent Roll angle = %d        Current Pitch Angle = %d \n\r ", roll, pitch);
	    display_roll(roll);
	    display_pitch(pitch);
	}
}

