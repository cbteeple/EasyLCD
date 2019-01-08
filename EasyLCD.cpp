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


#include "EasyLCD.h"
#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//===================================================
// PUBLIC FUNCTIONS

// Constructor
EasyLCD::EasyLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t char_size){
	_lcd = new LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows, char_size);
  _lcd_addr=lcd_addr;
}

// Deconstructor
EasyLCD::~EasyLCD(){
	delete _lcd;
}

// Start the LCD 
bool EasyLCD::begin() {
  // Check if LCD is plugged in
  Wire.beginTransmission(_lcd_addr);
  byte error = Wire.endTransmission();

  if (error != 0){
    return false;
  }
  else{
    _lcd->begin();
    return true;
  }
}


// Turn the display on/off (quickly)
void EasyLCD::noDisplay() {
	_lcd->noDisplay();
}
void EasyLCD::display() {
	_lcd->display();
}


// Turn the backlight on/off
void EasyLCD::noBacklight(void) {
	_lcd->noBacklight();
}

void EasyLCD::backlight(void) {
	_lcd->backlight();
}


// Send a string to the screen, taking newlines and
// overflow into account
void EasyLCD::write(String inStr){
  bool secondLine = false;

  if(_fadeOnUpdateOn){
  	fadeOut();
  }

  _lcd->clear();
  _lcd->setCursor(0,0);
  for (int i=0;i<inStr.length();i++){
    if ((i==16 & !secondLine) | inStr.charAt(i)=='\n'){
      _lcd->setCursor(0,1);
    }

    if (inStr.charAt(i)!='\n'){
      _lcd->write(inStr.charAt(i));
    }
   
  }

  if(_fadeOnUpdateOn){
  	fadeIn();
  }

}

// Set the fade time
void EasyLCD::fadeTime(uint16_t numMilliseconds){
	_fadeTime = numMilliseconds;
}


// Perform fade out
void EasyLCD::fadeOut (){
  for (int i=0; i<_fadeTime; i++){
    _lcd->noBacklight();
    delayMicroseconds((i));
    _lcd->backlight();
    delayMicroseconds((_fadeTime-i));
  }
  
  _lcd->noBacklight();
}


// Perform fade in
void EasyLCD::fadeIn (){
  for (int i=0; i<_fadeTime; i++){
    _lcd->noBacklight();
    delayMicroseconds((_fadeTime-i));
    _lcd->backlight();
    delayMicroseconds(i);
  }

}


// Fade between successive inputs of text?
void EasyLCD::fadeOnUpdate(bool state){
  _fadeOnUpdateOn = state;
}



//===================================================
// PRIVATE FUNCTIONS
bool EasyLCD::getBacklight() {
  return _lcd->getBacklight();
}
