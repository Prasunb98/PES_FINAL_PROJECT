/*
 * calibrate.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */


#include "calibrate.h"


// TO negate the calculated offset values
#define NEGATE (-1)

//TO covert 16bit values to 14bit by dividing them by 4 i.e right shift 2 times
#define Convert_to_14 (4)

//TO SET the calibration offset values by dividing it by 8
#define OFFSET (8)

// MAcro to buffer range of acceleration values
#define ACC_BUFFER (1000)

/*
 *   For documentation please visit- calibrate.h
 */
void accel_calibrate()
{

    PRINTF("Calibrating- \n\r");
    uint8_t Acc_Data[6];
    int16_t Acc_Out_14bit[3];
    int16_t Xoffset, Yoffset, Zoffset;


	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);


    int i;
    // Read five bytes in repeated mode
    for( i=0; i<5; i++)
    {
       Acc_Data[i] = i2c_repeated_read(0);
    }

    // Read last byte ending repeated mode
    Acc_Data[i] = i2c_repeated_read(1);

    for ( i=0; i<3; i++ )
    {
     	Acc_Out_14bit[i] = (int16_t) (((Acc_Data[2*i]<<8) | Acc_Data[2*i+1]) >>2);
    }



    Xoffset = Acc_Out_14bit[0] / OFFSET * NEGATE;                        // Compute X-axis offset correction value
    Yoffset = Acc_Out_14bit[1] / OFFSET * NEGATE;                        // Compute Y-axis offset correction value
    Zoffset = (Acc_Out_14bit[2] - COUNTS_PER_G) / OFFSET * NEGATE;       // Compute Z-axis offset correction value


    //  Standby mode to allow writing to the offset register


    i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);
    i2c_write_byte(MMA_ADDR, OFF_X_REG, Xoffset);
    i2c_write_byte(MMA_ADDR, OFF_Y_REG, Yoffset);
    i2c_write_byte(MMA_ADDR, OFF_Z_REG, Zoffset);
    i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x3D);


}


/*
 *  For documentation please visit- calibrate.h
 */

void Read_ACCxyz( int16_t *acc_values)
{
	int i;
	uint8_t Data[6];
	int16_t temp[3];

	i2c_start();
    i2c_read_setup(MMA_ADDR , REG_XHI);

    // Read five bytes in repeated mode
    for( i=0; i<5; i++)
    {
        Data[i] = i2c_repeated_read(0);
    }

    // Read last byte ending repeated mode
    Data[i] = i2c_repeated_read(1);

    for ( i=0; i<3; i++ )
    {
       temp[i] = (int16_t) ((Data[2*i]<<8) | Data[2*i+1]);  //compute 14-bit X,Y,Z output values
    }

    //converting to 16 bit values
    acc_values[0] = temp[0]/Convert_to_14;
    acc_values[1] = temp[1]/Convert_to_14;
    acc_values[2] = temp[2]/Convert_to_14;

}



