/*
 * i2c.c
 *
 *  Created on: Apr 29, 2022
 *      Author: prasunbiswas
 *      @Reference - Dean's book
 */



#include "i2c.h"


/*
 * REQUIRED MACROS for I2C
 *
 */
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN	    I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 		i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK             I2C0->C1 &= ~I2C_C1_TXAK_MASK

#define WAIT_TIME (200)

// Variable keeping track of I2C busy or free
int lock_detection=0;
int i2c_lock=0;



/*
 *  For documentation please visit - i2c.h
 */
void i2c_init(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*
 *  For documentation please visit - i2c.h
 */

void i2c_busy(void)
{
	// Start Signal
	lock_detection=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; /* set MASTER mode */
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->D = 0xFF;

	/* wait interrupt */
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {
	}

	/* clear interrupt bit */
	I2C0->S |= I2C_S_IICIF_MASK;

	/* Clear arbitration error flag*/
	I2C0->S |= I2C_S_ARBL_MASK;


	/* Send start */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;

	/* Set transmit mode */
	I2C0->C1 |= I2C_C1_TX_MASK;

	/* START signal generated */
	I2C0->C1 |= I2C_C1_MST_MASK;

	/*Wait until start is send*/
	I2C0->C1 |= I2C_C1_IICEN_MASK;


	/* Send stop */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; /* set SLAVE mode */
	I2C0->C1 &= ~I2C_C1_TX_MASK;  /* Set Receiver */
	I2C0->C1 |= I2C_C1_IICEN_MASK;


							          /* wait */
	/* Clear arbitration error & interrupt flag*/
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;

	// Updating the flags
	lock_detection=0;
	i2c_lock=1;
}

/*
 *  For documentation please visit - i2c.h
 */
void i2c_wait(void)
{
	lock_detection = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detection < WAIT_TIME)) {
		lock_detection++;
	}
	if (lock_detection >= WAIT_TIME)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}


/*
 *  For documentation please visit - i2c.h
 */
void i2c_start()
{
	I2C_TRAN;			/*set to transmit mode */
	I2C_M_START;		/*send start	*/
}


/*
 *  For documentation please visit - i2c.h
 */
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;
	I2C_WAIT

	I2C0->D =  address;
	I2C_WAIT

	I2C_M_RSTART;
	I2C0->D = (dev|0x1);
	I2C_WAIT

	I2C_REC;

}


/*
 *  For documentation please visit - i2c.h
 */

uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detection = 0;

	if(isLastRead)	{
		NACK;
	} else

	{
		ACK;
	}

	data = I2C0->D;
	I2C_WAIT

	if(isLastRead)	{
		I2C_M_STOP;
	}
	data = I2C0->D;

	return  data;
}


/*
 *  For documentation please visit - i2c.h
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;				 /*set to transmit mode */
	I2C_M_START;			 /*send start	*/
	I2C0->D = dev;			 /*send dev address	*/
	I2C_WAIT				 /*wait for completion */

	I2C0->D =  address;		 /*send read address	*/
	I2C_WAIT				 /*wait for completion */

	I2C_M_RSTART;			 /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT				 /*wait for completion */

	I2C_REC;			     /*set to recieve mode */
	NACK;					 /*set NACK after read	*/

	data = I2C0->D;			 /*dummy read	*/
	I2C_WAIT				 /*wait for completion */

	I2C_M_STOP;				 /*send stop	*/
	data = I2C0->D;			 /*read data	*/

	return data;
}


/*
 *  For documentation please visit - i2c.h
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;				 /*set to transmit mode */
	I2C_M_START;			 /*send start	*/
	I2C0->D = dev;			 /*send dev address	*/
	I2C_WAIT				 /*wait for ack */

	I2C0->D =  address;		 /*send write address	*/
	I2C_WAIT

	I2C0->D = data;			 /*send data	*/
	I2C_WAIT
	I2C_M_STOP;

}
