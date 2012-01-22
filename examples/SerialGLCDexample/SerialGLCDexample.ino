// SerialGLCD requires SoftwareSerial to work, so make sure that's included too
#include <SerialGLCD.h>
#include <SoftwareSerial.h>

// Create a new SerialGLCD object, and specify:
//   the transmit pin it is connected to (must be a PWM-capable pin)
SerialGLCD glcd(2, 3);

// Example setup
void setup() {

  // initialise the Serial connection and clear the screen
  glcd.begin();
  delay(200);
  glcd.setDutyCycle(50);
}

// Example loop
void loop() {
  
  // Clear the screen
  glcd.clear();
  delay(200);
  
  // Set the desired origin point for measurements
  // (0,0) is the top-left corner.
  glcd.setOrigin(0, 0);

  // LINES
  // Draw a bunch of lines
  int x1 = 0;
  int y1 = 32;
  int x2 = 64;
  int y2 = 32;
  for (int i = 0; i <= 7; i++) {
    glcd.drawLine(x1, y1, x2, y2);
    delay(50);
    x1+=8;
    y2-=4;
  }
  for (int i = 0; i <= 7; i++) {
    glcd.drawLine(x1, y1, x2, y2);
    delay(50);
    x1+=8;
    y2+=4;
  }
  for (int i = 0; i <= 7; i++) {
    glcd.drawLine(x1, y1, x2, y2);
    delay(50);
    x1-=8;
    y2+=4;
  }
  for (int i = 0; i <= 7; i++) {
    glcd.drawLine(x1, y1, x2, y2);
    delay(50);
    x1-=8;
    y2-=4;
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
  glcd.setOrigin(96, 48);
  
  // draw some little boxes in the middle of the screen
  for (int i = 0; i < 5; i++) {
    glcd.drawRectangle(-(i*5), -(i*5), (i*5), (i*5));
    delay(500);
  }
  
  // put some plain text
//  glcd.drawAscii("Hello!");
}
