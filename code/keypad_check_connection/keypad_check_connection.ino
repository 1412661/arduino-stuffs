#include <SerialCommand.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <EEPROM.h>

LiquidCrystal lcd(9);
SerialCommand SCmd;

int step;

int password[255];
int password_length;

int PASSWORD[255];
int PASSWORD_LENGTH;

void setup() {  
  lcd.begin(16,2);

  Serial.begin(115200);
  SCmd.addCommand("PUSH", PUSH);
  SCmd.addCommand("CLEAR", CLEAR);
  SCmd.addCommand("ENTER", ENTER);    
}

void loop() {
  SCmd.readSerial();
}

void ENTER() {

  Serial.println("ENTER");
}

void CLEAR() { 
  Serial.println("CLEAR");
}

void PUSH() {
  byte arg = atoi(SCmd.next()); 
  Serial.println(arg);
}



