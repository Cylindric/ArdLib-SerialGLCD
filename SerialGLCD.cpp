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
#include <SoftwareSerial.h>

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
static const uint8_t GLCDCMD_FILLED_BOX = 0x12;
static const uint8_t GLCDCMD_LINE = 0x0C;
static const uint8_t GLCDCMD_PIXEL = 0x10;
static const uint8_t GLCDCMD_PX_OFF = 0x00;
static const uint8_t GLCDCMD_PX_ON = 0x01;
static const uint8_t GLCDCMD_RESET = 0x06;
static const uint8_t GLCDCMD_REVERSE = 0x12;
static const uint8_t GLCDCMD_SET_FONT_MODE = 0x0A;
static const uint8_t GLCDCMD_SETX = 0x18;
static const uint8_t GLCDCMD_SETY = 0x19;
static const uint8_t GLCDCMD_SPLASH = 0x13;
static const uint8_t GLCDCMD_TOGGLE_FONT = 0x08;

SerialGLCD::SerialGLCD(uint8_t transmitPin, uint8_t width, uint8_t height) : _serial(SoftwareSerial(0, transmitPin)) {
  this->_txPin = transmitPin;
  this->_width = width;
  this->_height = height;
}

void SerialGLCD::begin() {
  this->_serial.begin(115200);
  this->clear();
  this->flush();
}

void SerialGLCD::clear() {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_CLEAR);
  this->flush();
}

void SerialGLCD::reset() {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_RESET);
  this->flush();
}

void SerialGLCD::toggleReverse() {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_REVERSE);
  this->flush();
}

void SerialGLCD::toggleSplashScreen() {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_SPLASH);
  this->flush();
}

void SerialGLCD::setDutyCycle(uint8_t percent) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_DUTYCYCLE);
  this->_serial.write(percent);
  this->flush();
}

void SerialGLCD::setBaudRate(uint16_t rate) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_BAUD);
  switch (rate) {
    case 4800:
      this->_serial.write(0x01);
      break;
    
    case 9600:
      this->_serial.write(0x02);
      break;
    
    case 19200:
      this->_serial.write(0x03);
      break;
    
    case 38400:
      this->_serial.write(0x04);
      break;
    
    case 57600:
      this->_serial.write(0x05);
      break;
    
    else:
      this->_serial.write(0x06);
      break;
  }
  this->flush();
}

void SerialGLCD::toggleFont() {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_TOGGLE_FONT);
  this->flush();
}

void SerialGLCD::setFontMode(uint8_t mode) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_SET_FONT_MODE);
  this->flush();
}

void SerialGLCD::gotoX(uint8_t x) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_SETX);
  this->_serial.write(x);
  this->flush();
}

void SerialGLCD::gotoY(uint8_t y) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_SETY);
  this->_serial.write(y);
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
  this->_serial.print(text);
  this->flush();
}

void SerialGLCD::drawAscii(int number) {
  this->_serial.print(number);
  this->flush();
}

void SerialGLCD::drawPixel(uint8_t x, uint8_t y, bool state) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_PIXEL);
  this->_serial.write(this->_originX + x);
  this->_serial.write(this->_originY + y);
  this->_serial.write(state ? GLCDCMD_PX_ON : GLCDCMD_PX_OFF);
  this->flush();
}

void SerialGLCD::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_LINE);
  this->_serial.write(this->_originX + x1);
  this->_serial.write(this->_originY + y1);
  this->_serial.write(this->_originX + x2);
  this->_serial.write(this->_originY + y2);
  this->_serial.write(state ? GLCDCMD_PX_ON : GLCDCMD_PX_OFF);
  this->flush();
}

void SerialGLCD::drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_BOX);
  this->_serial.write(this->_originX + x1);
  this->_serial.write(this->_originY + y1);
  this->_serial.write(this->_originX + x2);
  this->_serial.write(this->_originY + y2);
  this->_serial.write(state ? GLCDCMD_PX_ON : GLCDCMD_PX_OFF);
  this->flush();
}

void SerialGLCD::drawFilledBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fillbyte) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_FILLED_BOX);
  this->_serial.write(this->_originX + x1);
  this->_serial.write(this->_originY + y1);
  this->_serial.write(this->_originX + x2);
  this->_serial.write(this->_originY + y2);
  this->_serial.write(fillbyte);
  this->flush();
}

void SerialGLCD::drawCircle(uint8_t x, uint8_t y, uint8_t radius, bool state) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_CIRCLE);
  this->_serial.write(this->_originX + x);
  this->_serial.write(this->_originY + y);
  this->_serial.write(radius);
  this->_serial.write(state ? GLCDCMD_PX_ON : GLCDCMD_PX_OFF);
  this->flush();
}

void SerialGLCD::eraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  this->_serial.write(GLCDCMD_COMMAND);
  this->_serial.write(GLCDCMD_ERASE);
  this->_serial.write(this->_originX + x1);
  this->_serial.write(this->_originY + y1);
  this->_serial.write(this->_originX + x2);
  this->_serial.write(this->_originY + y2);
  this->flush();
}

void SerialGLCD::flush() {
  uint32_t now = millis();
  uint32_t next = this->_lastCmd + 100;
  if (now < next) {
    delay(next - now);
  }
  this->_lastCmd = millis();
}