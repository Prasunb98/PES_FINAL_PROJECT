# PES_FINAL_PROJECT


Title - Monitoring and displaying Different Parameters of anUnmanned Aircraft


The purpose of this project is to design a sensing system on unmanned aircraft using some sensing modules. 

Firstly, The MMA8451Q on-board digital accelerometer is used to measure the roll and pitch angles which will help to regulate the speed of the motor/ brightness of the LED using PWM - In my case I have used to change the brightness of the lEDs. 

Secondly, a LM35 temperature sensor will be used to measure the temperature. Finally after gathering these three inputs such as temperature, roll and pitch angles, it will be shown on the terminal through UART and also on the LCD, for better user interfacing.

In the first case, the on-board accelerometer is first calibrated by pushing the pushbutton after keeping it on a flat surface to get the accurate reading of accelerometer values; after which x,y,z values will be taken and then these values will be used to get the roll and pitch angles using cartesian geometry. 

After getting the Roll and pitch angles those data will be shown on the UART and simultaneously on LCD for better user interface. 
Now based on the certain roll and pitch angles the lED will change its brightness relatable to the situation where the motors will increase or decrease based on roll and pitch angles. if front and back LEDs will glow green and white respectively. and the right and left LED will glow blue and red respectively. In still situations no LED will glow. 

In the second case LM35 is being used and it needs ADC implementation to get the temperature data. 
Slope of the temperature sensor is speciFied as 10mv/C, so the slope is linear and the voltage is increased by 10mv for 1 degree rise in temperature. So the temperature can be calculated using 10 bit ADC with reference voltage of 3.0v .
T = (((3.0 * ADC_reading) /1024)/ 1000)/10 which is equivalent to; T = (adc_reading *300)/1024

LM35 is connected to channel ADC0_15 which is PTC1 (A5) of kl25z. 
after initializing the ADC peripheral in single ended mode- and reading the analog data followed by converting it using the mathematical formula mentioned earlier ; the temperature is then shown on the LCD and UART. Whenever there is any change in temperature the data will get reflected in the UART. 

Hence the objective of my project according to the proposal is completed. 

In case of testing scenario, I have used Manual Testing mode->
  For the accelerometer, I have checked whether the brightness of the LED is changing as per the rotation of the board in left,right,front and back which satisfies my testing part of the accelerometer. 
  
  In the case of LM35 i have checked using the normal room temperature which was coming equal to what i expected. 
  The LCD is also showing the same data as coming in UART. 
  
 Working demo Link - 



