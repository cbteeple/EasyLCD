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


//Constructor
EasyLCD::EasyLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t char_size){
	_lcd = new LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows, char_size);
}

EasyLCD::~EasyLCD(){
	delete _lcd;
}


//===================================================
//PUBLIC

void EasyLCD::begin() {
	_lcd->begin();
}


// Turn the display on/off (quickly)
void EasyLCD::noDisplay() {
	_lcd->noDisplay();
}
void EasyLCD::display() {
	_lcd->display();
}


// Turn the (optional) backlight off/on
void EasyLCD::noBacklight(void) {
	_lcd->noBacklight();
}

void EasyLCD::backlight(void) {
	_lcd->backlight();
}


void EasyLCD::write(String inStr){
  bool secondLine = false;

  if(_fadeBetweenOn){
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

  if(_fadeBetweenOn){
  	fadeIn();
  }

}


//Fade between successive inputs of text?
void EasyLCD::fadeBetween(bool fadeBetweenIn){
	_fadeBetweenOn = fadeBetweenIn;
}

void EasyLCD::fadeBetweenTime(uint16_t fadeBetweenTimeIn){
	_fadeBetweenTime = fadeBetweenTimeIn;
}



void EasyLCD::fadeOut (){
  for (int i=0; i<_fadeBetweenTime; i++){
    _lcd->noBacklight();
    delayMicroseconds((i));
    _lcd->backlight();
    delayMicroseconds((_fadeBetweenTime-i));
  }
  
  _lcd->noBacklight();
}


void EasyLCD::fadeIn (){
  for (int i=0; i<_fadeBetweenTime; i++){
    _lcd->noBacklight();
    delayMicroseconds((_fadeBetweenTime-i));
    _lcd->backlight();
    delayMicroseconds(i);
  }

}




//===================================================
//PRIVATE
bool EasyLCD::getBacklight() {
  return _lcd->getBacklight();
}
