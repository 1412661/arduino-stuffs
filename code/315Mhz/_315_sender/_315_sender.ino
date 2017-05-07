//4 bit first for id, next 10 bit for sensor value, the rest is no function
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
long data,sensor,id = 15;

void setup() {
  mySwitch.enableTransmit(10); //Arduino pin 10  <---> data pin of 315
}

void loop() {
  sensor = analogRead(A0);
  data = id << (24-4);
  data |= sensor << (24-14);
  mySwitch.send(data, 24);
  delay(10);
}

