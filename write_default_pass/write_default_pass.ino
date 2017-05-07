#include <EEPROM.h>

void setup() {
  EEPROM.write(0,6);delay(100);
  delay(100);
  EEPROM.write(1,1);
  delay(100);
  EEPROM.write(2,2);delay(100);
  EEPROM.write(3,3);delay(100);
  EEPROM.write(4,4);delay(100);
  EEPROM.write(5,5);delay(100);
  EEPROM.write(6,6);delay(100);
}

void loop(){
  
}
