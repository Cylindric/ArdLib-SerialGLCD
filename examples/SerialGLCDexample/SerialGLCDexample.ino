// SerialGLCD requires SoftwareSerial to work, so make sure that's included too
#include <SerialGLCD.h>
#include <SoftwareSerial.h>

// Create a new SerialGLCD object, and specify:
//   the transmit pin it is connected to (must be a PWM-capable pin)
SerialGLCD glcd(3, 2);

// Example setup
void setup() {

  // initialise the Serial connection and clear the screen
  glcd.begin();
  glcd.setDutyCycle(50);
}

// Example loop
void loop() {
  
  // Clear the screen
  glcd.clear();
  
  // Set the desired origin point for measurements
  // (0,0) is the top-left corner.
  glcd.setOrigin(0, 0);

  // LINES
  // Draw a bunch of lines
  for (int i = 0; i<=5; i++) {
    glcd.drawLine(0, 38+(i*5), 0+(i*5), 63);
  }

  // CIRCLES 
  // Draw a circle, then one inside it, and erase the middle one
  glcd.drawCircle(15, 15, 13);
  for (int i = 0; i<=5; i++) {
    glcd.drawCircle(15, 15, 10);
    delay(300);
    glcd.drawCircle(15, 15, 10, false);
    delay(300);
  }

  // Move the origin to the centre
  glcd.setOrigin(64, 32);
  
  // draw some little boxes in the middle of the screen
  for (int i = 0; i < 5; i++) {
    glcd.drawRectangle(-(i*5), -(i*5), (i*5), (i*5));
    delay(500);
  }
  
  // put some plain text
//  glcd.drawAscii("Hello!");
}
