/*
	EasyLCD.h
	Purpose: This library creates an easy-to-use interface for sending
	full strings to i2c LCD screens. It also adds some functionallity
	by allowing fading of the backlight on and off.

	@author   Clark Teeple
	@email    cbteeple@gmail.com
	@website  https://github.com/cbteeple/EasyLCD
	@version  0.1 2019_01_07
*/

#ifndef EASYLCD_H
#define EASYLCD_H

#include <LiquidCrystal_I2C.h>
#include <inttypes.h>

/**
 * After creating an instance of this class, first call begin() before anything else.
 * The backlight is on by default, since that is the most likely operating mode in
 * most cases.
 */
class EasyLCD
{
	public:
		/**
		 * Constructor
		 *
		 * @param lcd_addr	I2C slave address of the LCD display.
		 * @param lcd_cols	Number of columns your LCD display has.
		 * @param lcd_rows	Number of rows your LCD display has.
		 * @param charsize	The size in dots that the display has, use LCD_5x10DOTS or LCD_5x8DOTS.
		 					(or leave blank for default)
		 */
		EasyLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);

		~EasyLCD();

		/**
		 * Start up the LCD display (must be called before anything else is done).
		 *
		 * @return success or failure (is the lcd connected at the address given?)
		 */
		bool begin();


		 /**
		  * Do not show any characters on the LCD display. Backlight state will remain unchanged.
		  * This saves what was on the display, and will show it when enabled again.
		  */
		void noDisplay();

		/**
		 * Show the characters on the LCD display. This is the normal behaviour. This method should
		 * only be used after noDisplay() has been used.
		 */
		void display();

		/**
		 * Turn off the backlight
		 */
		void noBacklight();

		/**
		 * Turn on the backlight
		 */
		void backlight();
		
		/**
		 * Write a string to the lcd screen taking newline characters and overflow into account
		 *
		 * @param inStr	The string to write, including newlines. If the string is longer than
		 *				each line, it will continue on the next line.
		 */
		void write(String);

		/**
		 * Write a string to the lcd screen starting at a position
		 *
		 * @param inStr	The string to write. This function does not take newlines into account.
		 * @param row 	The row to start printing at (zero-indexed).
		 * @param col 	The column to start printing at (zero-indexed).
		 */
		void writeAtPosition(String inStr,int row,int col);

		/**
		 * Perform a backlight fade-out using the timing parameter set in "fadeBetweenTime()"
		 *     This is a neat hack using pulse-width modulation (turning the backlight on
		 *     and off really fast)
		 */
		void fadeOut();

		/**
		 * Perform a backlight fade-in using the timing parameter set in "fadeBetweenTime()"
		 */
		void fadeIn ();

		/**
		 * Set the duration of all fade operations
		 * 
		 * @param numMilliseconds	The duration of fade operations (in ms)
		 */
		void fadeTime(uint16_t);

		/**
		 * Decide whether or not to fade off-and-on every time the screen is updated
		 * 
		 * @param state	True or False?
		 */
		void fadeOnUpdate(bool);

		void clearOnUpdate(bool);


	private:

		/**
		 * Get the state of the backlight
		 */
		bool getBacklight();

		// Parameters
		LiquidCrystal_I2C * _lcd;
		uint8_t _lcd_addr;
		bool _fadeOnUpdateOn = false;
		bool _clearOnUpdateOn = true;
		uint16_t _fadeTime = 500; //[ms]

};

#endif // EASYLCD_H
