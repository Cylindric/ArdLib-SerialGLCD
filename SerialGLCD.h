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

#ifndef SerialGLCD_h
#define SerialGLCD_h

#include <inttypes.h>
#include <SoftwareSerial.h>

class SerialGLCD
{
  private:
    uint8_t _txPin;
    uint8_t _width;
    uint8_t _height;
    uint8_t _originX;
    uint8_t _originY;
    uint32_t _lastCmd;
    SoftwareSerial _serial;
    void flush();

  public:
    SerialGLCD(uint8_t transmitPin, uint8_t width, uint8_t height);
    void begin();
    void clear();
    void demo();
    void gotoX(uint8_t x);
    void gotoY(uint8_t y);
    void gotoXY(uint8_t x, uint8_t y);
    void toggleReverse();
    void toggleSplashScreen();
    void setDutyCycle(uint8_t percent);
    void setBaudRate(uint8_t ratecode);
    void setOrigin(uint8_t x, uint8_t y);
    
    void drawAscii(char* text);
    void drawAscii(int number);
    void drawPixel(uint8_t x, uint8_t y, bool state = true);
    void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state = true);
    void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state = true);
    void drawCircle(uint8_t x, uint8_t y, uint8_t radius, bool state = true);
    void eraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
    
};

#endif
