#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

byte speed_reader = A0;
byte speed_pin = A1;

int data = 5;

int latchPin = 5;
int clockPin = 6;
int dataPin = 7;

void setup() {
  Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  analogWrite(speed_pin, 254);
  stand();
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

//up down left right
void loop() {
  data = mySwitch.getReceivedValue();
  Serial.println(data);
  
  if (data == 5) receiving(); 
  else 
    if (data == 1) turn(0B10001010); 
  else
    if (data == 2) turn(0B10010100); 
    else 
      if (data == 3) turn(0B10010010); 
    else
      if (data == 4) turn(0B10001100); 
      else
        disconnected();
}

void receiving() {
  turn(0);
}

void disconnected() {
  turn(0B00000000);
}

void stand() {
  turn(0);
}

void turn(byte bits) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, bits);
  digitalWrite(latchPin, HIGH);  
  delayMicroseconds(10);
}

