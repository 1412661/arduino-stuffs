#include <SerialCommand.h>

//Pin connected to ST_CP (pin 12) of 74HC595
byte latchPin = 8;
//Pin connected to SH_CP (pin 11) of 74HC595
byte clockPin = 9;
////Pin connected to DS (pin 14) of 74HC595
byte dataPin = 10;
byte lightPin = A0;
byte k;

void setup() {
   pinMode(latchPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   pinMode(dataPin, OUTPUT);
   pinMode(lightPin, INPUT);
   Serial.begin(9600);
}

void loop(){
  int reading  = analogRead(lightPin);
  int numLEDSLit = reading / 90;  //1023 / 9 / 2
  if (numLEDSLit > 8) numLEDSLit = 8;
  Serial.println("-------------");
  Serial.println(numLEDSLit);
  
  k = 0B00000000;
  for (int i = 0; i <= numLEDSLit-1; i++) {
    k |= (k << i);
  }
  out(k);
  Serial.println(k);
  Serial.println("-------------");
  delay(1000);
}

void out(byte data) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}
