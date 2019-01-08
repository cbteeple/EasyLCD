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
 * This is the driver for the Liquid Crystal LCD displays that use the I2C bus.
 *
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
		 * @param lcd_addr	I2C slave address of the LCD display. Most likely printed on the
		 *					LCD circuit board, or look in the supplied LCD documentation.
		 * @param lcd_cols	Number of columns your LCD display has.
		 * @param lcd_rows	Number of rows your LCD display has.
		 * @param charsize	The size in dots that the display has, use LCD_5x10DOTS or LCD_5x8DOTS.
		 */
		EasyLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);

		~EasyLCD();
		/**
		 * Set the LCD display in the correct begin state, must be called before anything else is done.
		 */
		void begin();


		 /**
		  * Do not show any characters on the LCD display. Backlight state will remain unchanged.
		  * Also all characters written on the display will return, when the display in enabled again.
		  */
		void display();

		/**
		 * Show the characters on the LCD display, this is the normal behaviour. This method should
		 * only be used after noDisplay() has been used.
		 */
		void noDisplay();

		void noBacklight();
		void backlight();
		
		void write(String);

		void fadeOut();
		void fadeIn ();
		void fadeBetweenTime(uint16_t);
		void fadeBetween(bool);

	private:
		bool getBacklight();
		LiquidCrystal_I2C * _lcd;
		bool _fadeBetweenOn = false;
		uint16_t _fadeBetweenTime = 500; //[ms]

};

#endif // FDB_LIQUID_CRYSTAL_I2C_H
