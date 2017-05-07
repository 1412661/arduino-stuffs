#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
#include <Servo.h> 
Servo servo;

int rain = A0;
long id = 5;

void setup() {
  mySwitch.enableTransmit(10);
  servo.attach(9);
  servo.write(120);
}

void loop() {
  if (analogRead(rain) < 410) {
    mySwitch.send(id << 20,24);
    servo.write(0);
  }
  else {
    mySwitch.send((id << 20) | (1 << 19),24);
    servo.write(120);
    delay(15000);
  }
  
  delay(10000);  
}


