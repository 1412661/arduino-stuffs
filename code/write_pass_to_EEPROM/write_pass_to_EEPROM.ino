#include <EEPROM.h>

/* CONFIG  */
byte password[255] = {
  2,3,5,5,8};
byte passlen = 5;

void setup() {
  Serial.begin(9600);
  EEPROM.write(0,passlen);
  for (byte i = 1; i <= passlen; i++) {
    EEPROM.write(i,password[i-1]); 
  }
  Serial.println("Password writing complete !");


  Serial.println();
  Serial.println();
  Serial.print("Password length: ");
  Serial.println(EEPROM.read(0));
  Serial.print("Password is: ");
  for (byte i = 1; i <= passlen; i++) {
    Serial.print(EEPROM.read(i));
  }
}

void loop() {
}




