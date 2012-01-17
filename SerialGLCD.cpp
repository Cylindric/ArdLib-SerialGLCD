#include "Arduino.h"
#include "SerialGLCD.h"
#include <SoftwareSerial.h>

SerialGLCD::SerialGLCD() {
  this->_serial = SoftwareSerial(1,2);
}

void SerialGLCD::attach(uint8_t transmitPin) {
  this->_txPin = transmitPin;
}

void SerialGLCD::clear() {
}

void SerialGLCD::demo() {
}

void SerialGLCD::setX(uint8_t x) {
}

void SerialGLCD::setY(uint8_t y) {
}

void SerialGLCD::setXY(uint8_t x, uint8_t y) {
}
