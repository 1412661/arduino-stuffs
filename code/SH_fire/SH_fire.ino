#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

long temp;
int sensor = A0;
long id = 2;
long val;
int led = 13;

void setup() {
  mySwitch.enableTransmit(10);
  pinMode(led, OUTPUT);
}

void loop() {
  temp = round((5.0*analogRead(sensor)*100.0/1024.0));
  val = (id << 20) | (temp << 10);
  mySwitch.send(val,24);

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(5000); //1 phut
}




