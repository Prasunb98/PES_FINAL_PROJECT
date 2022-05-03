
/**
 * @file    Final_Project.c
 * Created on : 29th April
 * @brief   Application entry point.
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <math.h>
#include <roll_pitch.h>
#include "led.h"
#include "i2c.h"
#include "mma8451q.h"
#include "PWM.h"
#include "gpio.h"
#include "calibrate.h"
#include <stdint.h>
#include "init.h"
#include "systick.h"
#include "lcd.h"
#include "LM35.h"

int main(void)
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    	RGB_INIT();
    	i2c_init();	/* init i2c	*/
    	PWM_Init(); /* init pWM */
    	Init_GPIO(); /* Interrupt Button at port D7 is initialized */

    	/* Initialize your Board Support Package */
    	system_init();

    	/* Start LCD by initializing through commands */
    	start_lcd();

    	// until acceleration peripheral is initialized
    	if (!init_accel())
    	{
    		Control_RGB_LEDs(1, 0, 0);
    		while (1);
    	}


    	Flag_Interrupt = RESET;

	      /* Entering into super loop */
        while (1)
        	{

        		if(Flag_Interrupt)
        		{
        			// calibrating once the GPIO button is pressed
        			accel_calibrate();
        			Flag_Interrupt = RESET;

        		}
        		read_xyz();
        		roll_pitch_calculator();
        		Roll_Detector( );
        		Pitch_Detector( );

        		if (flag_1sec)
        				{
        					flag_1sec = 0;
        					scan_temperature();
        				}
        	}
}
