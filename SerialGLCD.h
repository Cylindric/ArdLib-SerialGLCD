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
    SoftwareSerial _serial;

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
    
    void drawAscii(char* text);
    void drawPixel(uint8_t x, uint8_t y, bool state = true);
    void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state = true);
    void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool state = true);
    void drawCircle(uint8_t x, uint8_t y, uint8_t radius, bool state = true);
    void eraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
    
};

#endif
