
/*
 *
 * @ MMA8451Q.c file
 * Created on: Apr 29, 2022
 *  @Author - Prasun Biswas
 *
 */


#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>
#include "i2c.h"
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include <MKL25Z4.H>
#include "lcd.h"

#define MMA_ADDR 0x3A

/*
 *  Register address from MMA8451 datasheet
 */
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define OFF_X_REG 0x2f
#define OFF_Y_REG 0x30
#define OFF_Z_REG 0x31

#define COUNTS_PER_G (4096.0)

// Pi value for Calculating Roll and Pitch angles
#define PI (3.14159265)

extern int roll, pitch;

extern int16_t acc_X, acc_Y, acc_Z;

/*
 *
 *   @This function initializes accelerometer sensor using details from dataSheet
 *                 i2c has to already be enabled
 *
 */
int init_accel(void);

/*
 *  @This function does I2C repeated mode is being used to read the registers
 *  containing X,Y,Z counts related to acceleration
 *
 */
void read_xyz(void);

/*
 * @ Description :Cartesian geometry is being used to calculate Roll and Pitch angles
 *
 */
void roll_pitch_calculator(void);

#endif
