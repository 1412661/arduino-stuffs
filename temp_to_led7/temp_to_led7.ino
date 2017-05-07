#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Pin connected to ST_CP (pin 12) of 74HC595
byte latchPin = 5;
//Pin connected to SH_CP (pin 11) of 74HC595
byte clockPin = 6;
//Pin connected to DS (pin 14) of 74HC595
byte dataPin = 7;
//Number of 8-bit shiftout

byte t1,t2,t3; 
byte N[] = {
  0B00000011,  //0
  0B10011111,  //1
  0B00100101,  //2
  0B00001101,  //3
  0B10011001,  //4
  0B01001001,  //5
  0B01000001,  //6
  0B00011111,  //7
  0B00000001,  //8
  0B00001001  //9
};

void setup() {
  sensors.begin();
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {  
  sensors.requestTemperatures();
  ConvertTemp(sensors.getTempCByIndex(0));
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, N[t3]);
  shiftOut(dataPin, clockPin, LSBFIRST, N[t2]);
  shiftOut(dataPin, clockPin, LSBFIRST, N[t1]);
  digitalWrite(latchPin, HIGH);
  
  delay(300);
}


void ConvertTemp(float temp) { //20~50 0C
  int tmp = round(temp*10);
  t3 = (tmp % 100) % 10;
  t2 = round(((tmp % 100) - t3) / 10);
  t1 = round((tmp - t2*10 - t3)/100);
}



