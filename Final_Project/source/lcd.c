/*
 * @lcd.c
 * Created on: Apr 29, 2022
 *Author - Prasun Biswas
 * Description- This enables all the functionality for lCD integration
 */



#include "lcd.h"


static void lcd_Cmd(uint8_t cmd);
static void write_nibble(uint8_t nibble);
static void delay(uint16_t cnt);


/*
 * For documentation please visit- lcd.h
 */
void start_lcd(void)
{
	lcd_Cmd(0x02);  // Move the cursor to original position
    lcd_Cmd(0x28);  // Enable 4-bit, 2 line, 5x7 dots mode for chars
	lcd_Cmd(0x0C);  // Display ON, Cursor OFF
	lcd_Cmd(0x01);  // Clear Display

	lcd_Cmd(0x80);
	lcd_string_write("T = ");
}


/*
 * For documentation please visit- lcd.h
 */

void display_temperature(uint8_t temp)
{
	static char lcd_str[] = "00 (C)"; /* temperature */
	static uint8_t prev_temp = 0;     /* Previous temperature */

	if (prev_temp != temp)
	{
		prev_temp = temp;

		/* Move cursor to 6th block on line 2 */
		lcd_Cmd(0x85);
		lcd_str[0] = ((uint8_t)(temp / 10)) + '0'; /* Higher digit in ASCII */
		lcd_str[1] = ((uint8_t)(temp % 10)) + '0'; /* Lower digit in ASCII */
		//lcd_string_write("  Temp: ");
		lcd_string_write(lcd_str); /* Write to LCD */

		PRINTF(" \n\r Change detected in Temp- \n \r", temp);
		PRINTF(" \n\r Current Temp = %d C \n\r \n \r", temp);
	}
}

/*
 * For documentation please visit- lcd.h
 *
 */

void display_roll(uint8_t input_roll)
{
	static char lcd_str[] = "00 ";
	static uint8_t prev_roll = 0;     /* Previous temperature */
	if (prev_roll != input_roll)
	{
		prev_roll = input_roll;

		lcd_Cmd(0xC0);
		lcd_string_write("R= ");

		lcd_str[0] = ((uint8_t)(input_roll/10)) + '0';
		lcd_str[1] = ((uint8_t)(input_roll%10)) + '0';

	 	lcd_string_write(lcd_str); /* Write to LCD */

	}
}

/*
 * For documentation please visit- lcd.h
 *
 */
void display_pitch(uint8_t input_pitch)
{
	static char lcd_str1[] = "";
	static uint8_t prev_pitch = 0;     /* Previous temperature */
	if (prev_pitch != input_pitch)
	{
		prev_pitch = input_pitch;


		lcd_Cmd(0xC7);
		lcd_string_write("P= ");
		lcd_str1[0] = ((uint8_t)(input_pitch/10)) + '0';
		lcd_str1[1] = ((uint8_t)(input_pitch%10)) + '0';


		lcd_string_write(lcd_str1); /* Write to LCD */

	}
}


/*
 * For documentation please visit- lcd.h
 *
 */

uint8_t lcd_string_write(char *str)
{
	uint8_t cnt = 0; // Counting string length

	// Write until entire string (msg) is finished
	// (max 16 char per line)
	while (*str && cnt < 16)
	{
		GPIOC->PDOR |=  LCD_RS; // Select data register    (RS=HIGH)
		GPIOC->PDOR &= ~LCD_RW; // Select write operation  (RW=LOW)

		write_nibble(*str & 0xF0); // Write Upper nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
    delay(10000);           // Wait for ~1msec
    GPIOC->PDOR &= ~LCD_E;  // EN=LOW
    delay(10000);           // Wait for ~1msec

		write_nibble((*str << 4) & 0xF0); // Write Lower nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
    delay(10000);           // Wait for ~1msec
    GPIOC->PDOR &= ~LCD_E;  // EN=LOW
    delay(10000);           // Wait for ~1msec

		str++;     // Go to next character
		cnt++;     // Increment string length check count
	}

	return cnt;
}

/*
 * For documentation please visit- lcd.h
 *
 */

static void lcd_Cmd(uint8_t cmd)
{
		GPIOC->PDOR &= ~LCD_RS; // Select command register (RS=LOW)
		GPIOC->PDOR &= ~LCD_RW; // Select write operation  (RW=LOW)

		write_nibble(cmd & 0xF0); // Write Upper nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
    delay(10000);           // Wait for ~1msec
    GPIOC->PDOR &= ~LCD_E;  // EN=LOW
    delay(10000);           // Wait for ~1msec

		write_nibble((cmd << 4) & 0xF0); // Write Lower nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
    delay(10000);           // Wait for ~1msec
    GPIOC->PDOR &= ~LCD_E;  // EN=LOW
    delay(10000);           // Wait for ~1msec
}



/*
 * For documentation please visit- lcd.h
 *
 */
static void write_nibble(uint8_t nibble)
{
		uint32_t gpio_temp;

		// Get GPIO-C Data Register
		gpio_temp = GPIOC->PDOR;

	  // Update the LCD data line DB7
		if (nibble & 0x80){
			gpio_temp |= LCD_DB7;
		}
		else{
			gpio_temp &= ~LCD_DB7;
		}

		// Update the LCD data line DB6
		if (nibble & 0x40){
			gpio_temp |= LCD_DB6;
		}
		else{
			gpio_temp &= ~LCD_DB6;
		}

		// Update the LCD data line DB5
		if (nibble & 0x20){
			gpio_temp |= LCD_DB5;
		}
		else{
			gpio_temp &= ~LCD_DB5;
		}

		// Update the LCD data line DB4
		if (nibble & 0x10){
			gpio_temp |= LCD_DB4;
		}
		else{
			gpio_temp &= ~LCD_DB4;
		}

		// Write updated data to GPIO-C Port
		GPIOC->PDOR = gpio_temp;
}



/*
 *
 * For documentation please visit- lcd.h
 *
 */

static void delay(uint16_t cnt)
{
  int i,j;
	for (j=0; j<5; j++)
	{
		for(i=0;i<cnt;i++);
	}
}
