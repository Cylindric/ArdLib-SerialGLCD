#include <SoftwareSerial.h>

SoftwareSerial lcd(2, 3);
int state = 1;
int blocked=false;

void setup() {
  Serial.begin(115200);
  lcd.begin(115200);
  delay(2000);
//  wr(0x7C); wr(0x01); wr(0x00); // debug
  wr(0x7C); wr(0x00); // clear
  delay(2000);
  Serial.println("Hello");
}

void loop() {
  for (int i = 0; i < 10; i++) {
    wr(0x7C); wr(0x0F); // box
    wr(10+(10*i+i)); wr(27); // x1,y1
    wr(20+(10*i+i)); wr(37); // x2,y2
    wr(state);
    delay(20);
  }
  state = (state==1 ? 0 : 1);
}

void wr(byte b) {  
  if (lcd.available()) {
//    while(lcd.available()) {
//      lcd.read();
//    }
//    Serial.print("on : ");
//    byte val = lcd.read();
//    if (val == 0x93) {
//      Serial.print("xoff?");
//      blocked = true;
//    } else {
//      Serial.print(val, HEX);
//    }
//    Serial.println();
//    delay(50);
  }
  
  // spin if blocked
//  while (blocked) {
//    if (lcd.available()) {
//      Serial.print("off: ");
//      byte val = lcd.read();
//      if (val == 0x91) {
//        Serial.print("xon?");
//        blocked = false;
//      }  else {
//        Serial.print(val, HEX);
//      }
//      Serial.println();
//    }    
//  }
  
  // send the byte
  lcd.write(b);
}
