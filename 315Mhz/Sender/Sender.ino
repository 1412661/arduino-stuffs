#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
byte up = 5;
byte down = 6;
byte left = 7;
byte right = 8;

void setup() {
  mySwitch.enableTransmit(10);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
}

void loop() {
  byte a = (digitalRead(up) ==HIGH) ? 1 : 0;
  byte b = (digitalRead(down) ==HIGH) ? 1 : 0;
  byte c = (digitalRead(left) ==HIGH) ? 1 : 0;
  byte d = (digitalRead(right) ==HIGH) ? 1 : 0;

  if (a + b + c + d != 3) {
    mySwitch.send(5,8);     
  } 
  else {
    if(a == 0) mySwitch.send(1,8);
    if (b == 0) mySwitch.send(2,8);
    if (c == 0) mySwitch.send(3,8);
    if (d == 0) mySwitch.send(4,8);
  } 
  delay(500);
}


