/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 *
 * This is based on the "SerialDisplay" example from LiquidCrystal_I2C
 */
#include <EasyLCD.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
unsigned int lcd_addr = 0x27;
EasyLCD lcd(lcd_addr, 16, 2);

bool lcdAttached = false;

void setup()
{
	// Initialize the LCD
	lcdAttached = lcd.begin();

	if (lcdAttached){
		// Perform a fade to initialize the screen
		lcd.fadeTime(350); // Set the fade time to 350 ms
		lcd.fadeOut(); 
		lcd.fadeIn();

		// Turn on the fade-out / fade-in effect when updating the screen
		// This effect is totally optional. It's a pretty cool hack.
		lcd.fadeOnUpdate(true);

		Serial.print("LCD initialized at i2c address: ");
	}
	else{
		Serial.print("LCD is NOT ATTACHED at i2c address: ");
	}

	Serial.println(lcd_addr,HEX);

	// Initialize the serial port at a speed of 9600 baud
	Serial.begin(9600);
}



void loop()
{
	if (lcdAttached){
		// If characters arrived over the serial port...
		if (Serial.available()) {
			// Wait a bit for the entire message to arrive
			delay(100);

			// Write all characters received with the serial port to the LCD.
			while (Serial.available() > 0) {
				String command = Serial.readStringUntil('\n');
				lcd.write(command);
			}
		}
	}
}




