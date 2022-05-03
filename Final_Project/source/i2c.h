/*
 * i2c.h
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 */


#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <MKL25Z4.H>


/*
 * @ This fucntion initializes i2c0 from the manual
 */
void i2c_init(void);

/*
 *  This function does the start sequence
 */
void i2c_start(void);

/*
 *  @This function Sets up the device from which data is read by sending device and register addresses
 *
 *  Parameter: Device and register address from which data has to be read
 *
 */
void i2c_read_setup(uint8_t dev, uint8_t address);

/*
 *  @This function keeps reading from i2c bus until the signal is to stop.
 *
 *  @Parameter:   Flag isLastRead to indicate the stop signal
 *
 */
uint8_t i2c_repeated_read(uint8_t);


/*
 * @This function is to read a single byte from device address
 *  Parameter :  Takes Device and the register address
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/*
 * @This function writes a byte data to the device address
 *  Parameters : Along with the Device and register address, 8 bit data is given
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif
