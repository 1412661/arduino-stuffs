/*
  Simple example for receiving
 
 http://code.google.com/p/rc-switch/
 
 Need help? http://forum.ardumote.com
 */

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

byte led1 = 6;
byte led2 = 7;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {

  int value = mySwitch.getReceivedValue();

  if (value != 0) {
    if (value == 5) digitalWrite(led1, HIGH);
    if (value == 10) digitalWrite(led1, LOW);
    if (value == 15) digitalWrite(led2, HIGH);
    if (value == 20) digitalWrite(led2, LOW);
  }
  
  delay(1);
}


