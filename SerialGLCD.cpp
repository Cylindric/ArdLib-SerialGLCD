/*
SerialGLCD.cpp - 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://github.com/Cylindric/ArdLib-SerialGLCD.
*/

#include "Arduino.h"
#include "SerialGLCD.h"
//#include <SoftwareSerial.h>

// Command-codes for the SparkFun SerialGLCD Backpack
// http://www.sparkfun.com/products/9352
static const uint8_t GLCDCMD_BAUD = 0x07;
static const uint8_t GLCDCMD_BOX = 0x0F;
static const uint8_t GLCDCMD_CIRCLE = 0x03;
static const uint8_t GLCDCMD_CLEAR = 0x00;
static const uint8_t GLCDCMD_COMMAND = 0x7C;
static const uint8_t GLCDCMD_DEMO = 0x04;
static const uint8_t GLCDCMD_DUTYCYCLE = 0x02;
static const uint8_t GLCDCMD_ERASE = 0x05;
static const uint8_t GLCDCMD_LINE = 0x0C;
static const uint8_t GLCDCMD_PIXEL = 0x10;
static const uint8_t GLCDCMD_PX_OFF = 0x00;
static const uint8_t GLCDCMD_PX_ON = 0x01;
static const uint8_t GLCDCMD_REVERSE = 0x12;
static const uint8_t GLCDCMD_SETX = 0x18;
static const uint8_t GLCDCMD_SETY = 0x19;
static const uint8_t GLCDCMD_SPLASH = 0x13;

// Small-font
static const uint8_t SMALLFONT_OFFSETS[] = {24, 16};
static const uint8_t SMALLFONT[] = {
  0,1, 0,2, 0,3, 0,4, 1,0, 1,5, 2,0, 2,5, 3,1, 3,2, 3,3, 3,4, // 0
  0,0, 0,4, 1,0, 0,2, 0,3, 0,4, 0,5, 1,0, // 1
};


//SerialGLCD::SerialGLCD(uint8_t transmitPin, uint8_t width, uint8_t height) : _serial(SoftwareSerial(0, transmitPin)) {
SerialGLCD::SerialGLCD(uint8_t transmitPin, uint8_t width, uint8_t height) {
  this->_txPin = transmitPin;
  this->_width = width;
  this->_height = height;
}

void SerialGLCD::begin() {
  Serial.begin(115200);
  this->clear();
  this->flush();
}

void SerialGLCD::clear() {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_CLEAR); 
  this->flush();
}

void SerialGLCD::demo() {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_DEMO);
  this->flush();
}

void SerialGLCD::toggleReverse() {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_REVERSE);
  this->flush();
}

void SerialGLCD::toggleSplashScreen() {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_SPLASH);
  this->flush();
}

void SerialGLCD::setDutyCycle(uint8_t percent) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_DUTYCYCLE);
  Serial.write(percent);
  this->flush();
}

void SerialGLCD::setBaudRate(uint8_t ratecode) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_BAUD);
  Serial.write(0x30 + ratecode);
  this->flush();
}

void SerialGLCD::gotoX(uint8_t x) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_SETX);
  Serial.write(x);
  this->flush();
}

void SerialGLCD::gotoY(uint8_t y) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_SETY);
  Serial.write(y);
  this->flush();
}

void SerialGLCD::gotoXY(uint8_t x, uint8_t y) {
  this->gotoX(x);
  this->gotoY(y);
  this->flush();
}

void SerialGLCD::setOrigin(uint8_t x, uint8_t y) {
  this->_originX = x;
  this->_originY = y;
  this->flush();
}

void SerialGLCD::drawAscii(char* text) {
  Serial.write(text);
  this->flush();
}

void SerialGLCD::drawPixel(uint8_t x, uint8_t y, bool state) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_PIXEL);
  Serial.write(this->_originX + x);
  Serial.write(this->_originY + y);
  if (state) {
    Serial.write(GLCDCMD_PX_ON);
  } else {
    Serial.write(GLCDCMD_PX_OFF);
  }
  this->flush();
}

void SerialGLCD::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_LINE);
  Serial.write(this->_originX + x1);
  Serial.write(this->_originY + y1);
  Serial.write(this->_originX + x2);
  Serial.write(this->_originY + y2);
  if (state) {
    Serial.write(GLCDCMD_PX_ON);
  } else {
    Serial.write(GLCDCMD_PX_OFF);
  }
  this->flush();
}

void SerialGLCD::drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_BOX);
  Serial.write(this->_originX + x1);
  Serial.write(this->_originY + y1);
  Serial.write(this->_originX + x2);
  Serial.write(this->_originY + y2);
  this->flush();
}

void SerialGLCD::drawCircle(uint8_t x, uint8_t y, uint8_t radius, bool state) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_CIRCLE);
  Serial.write(this->_originX + x);
  Serial.write(this->_originY + y);
  Serial.write(radius);
  if (state) {
    Serial.write(GLCDCMD_PX_ON);
  } else {
    Serial.write(GLCDCMD_PX_OFF);
  }
  this->flush();
}

void SerialGLCD::eraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  Serial.write(GLCDCMD_COMMAND);
  Serial.write(GLCDCMD_ERASE);
  Serial.write(this->_originX + x1);
  Serial.write(this->_originY + y1);
  Serial.write(this->_originX + x2);
  Serial.write(this->_originY + y2);
  this->flush();
}

void SerialGLCD::flush() {
  uint32_t now = millis();
  uint32_t next = this->_lastCmd + 200;
  if (now < next) {
    delay(next - now);
  }
  this->_lastCmd = millis();
}