// SerialGLCD requires SoftwareSerial to work, so make sure that's included too
#include <SerialGLCD.h>
#include <SoftwareSerial.h>

// Create a new SerialGLCD object, and specify:
//   the transmit pin it is connected to (must be a PWM-capable pin)
//   the width of the screen in pixels
//   the height of the screen in pixels
SerialGLCD glcd(3, 128, 64);

// Example setup
void setup() {

  // initialise the Serial connection and clear the screen
  glcd.begin();
  
  // draw some little box in the middle of the screen
  glcd.drawBox(59, 27, 79, 47);
  delay(500);
  glcd.drawBox(49, 22, 74, 42);
  delay(500);
  glcd.drawBox(54, 17, 69, 37);
  delay(2000);

  // put some plain text
  glcd.drawAscii("Hello!");
}

// Example loop
void loop() {
}
