#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

long id = 6;
int read_ = 9;
int write_ = 8;
int autolight = 1;
int state = 1;

int led = 13;

void setup() {
  mySwitch.enableReceive(0);
  pinMode(read_, INPUT);
  pinMode(write_, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {  
  long val = mySwitch.getReceivedValue();
  mySwitch.resetAvailable();
  
  if ((val >> 20) == id) {
      autolight = getBit(val,19);
      if (autolight == 0) state = getBit(val,18);
      blinkLED();      
  }
  
  if (!autolight) digitalWrite(write_, state);
   else {
     blinkLED();
     digitalWrite(write_, digitalRead(read_)); 
     delay(2000);
   }   
}


int getBit(long number, int position) {
  int bitmask = 1 << position;
  return (number & bitmask) ? 1 : 0;
}

void blinkLED() {
  digitalWrite(led, HIGH);
  delay(80);
  digitalWrite(led, LOW);
}

