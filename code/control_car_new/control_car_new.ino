#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

byte up = 2;
byte down = 3;
byte left = 5;
byte right = 6;
byte hold = 7;

//address: 0B0000000000001100

void setup() {
  mySwitch.enableTransmit(9);

  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(hold, INPUT_PULLUP);

}


void loop() {
  if (digitalRead(up) == LOW) left_();
  if (digitalRead(down) == LOW) right_();
  if (digitalRead(left) == LOW) up_();
  if (digitalRead(right) == LOW) down_();
  if (digitalRead(hold) == LOW) hold_();
  delay(5);
}

void up_() {
  mySwitch.send(0B000000000000110011001100,24); 
  delay(5);
}

void down_() {
 mySwitch.send(0B000000000000110000110011,24); 
  delay(5);
}

void left_() {
  mySwitch.send(0B000000000000110011000011,24); 
  delay(5);
}

void right_() {
  mySwitch.send(0B000000000000110000111100,24); 
  delay(5);
}

void hold_() {
  mySwitch.send(0B000000000000110000000000,24); 
  delay(5);
}



