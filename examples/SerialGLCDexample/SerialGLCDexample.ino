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
  glcd.setDutyCycle(50);
}

// Example loop
void loop() {
  
  // clear the screen
  glcd.clear();
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
  
  // draw some little box in the middle of the screen
  glcd.drawBox(-5, -5, 5, 5);
  delay(500);
  glcd.drawBox(-10, -10, 10, 10);
  delay(500);
  glcd.drawBox(-15, -15, 15, 15);
  delay(500);
  glcd.drawBox(-20, -20, 20, 20);
  delay(500);
  glcd.drawBox(-25, -25, 25, 25);
  delay(2000);

  
  // put some plain text
//  glcd.drawAscii("Hello!");
}
