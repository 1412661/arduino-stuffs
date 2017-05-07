#include <SerialCommand.h>

int latchPin = 5;
int clockPin = 6;
int dataPin = 7;

byte speed_pin = A1;

SerialCommand SCmd;   // The demo SerialCommand object

void setup(){  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(speed_pin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Ready for testing !");

  SCmd.addCommand("u",up);       
  SCmd.addCommand("d",down);       
  SCmd.addCommand("l",left);   
  SCmd.addCommand("r",right);  
  SCmd.addCommand("s",stand);

  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 


}

void loop()
{  
  SCmd.readSerial();     // We don't do much, just process serial commands
}

void speed_control() {
  analogWrite(speed_pin, 1000);
}

void up() {
  speed_control();
  turn(0B10001010);
}

void down() {
  speed_control();
  turn(0B10010100); 
}

void left() {
  speed_control();
  turn(0B10010010); 
}

void right() {
  speed_control();
  turn(0B10001100); 
}

void stand() {
  turn(0);
}

void unrecognized(){
  Serial.println("What ?"); 
}

void turn(byte bits) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, bits);
  digitalWrite(latchPin, HIGH);  
  delay(50);
}


