#include <EEPROM.h>

int address = 12;
int value = 51;

void setup() {
  Serial.begin(9600);
  
  EEPROM.write(address, value);
  
  int v = EEPROM.read(address);
  
  Serial.print("Address: ");
  Serial.println(address);
  Serial.print("Value: ");
  Serial.println(v);
  Serial.println();
}

void loop() {  
}
