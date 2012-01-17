#ifndef SerialGLCD_h
#define SerialGLCD_h

#include <inttypes.h>
#include <SoftwareSerial.h>

class SerialGLCD
{
  private:
    uint8_t _txPin;
    SoftwareSerial _serial;

  public:
    SerialGLCD();
    void attach(uint8_t transmitPin);
    void clear();
    void demo();
    void setX(uint8_t x);
    void setY(uint8_t y);
    void setXY(uint8_t x, uint8_t y);
};

#endif
