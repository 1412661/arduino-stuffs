#include <SerialCommand.h>
#include <AH_24Cxx.h>
#include <Wire.h> 

#define AT24C02  1

#define BUSADDRESS  0x50      
#define EEPROMSIZE  2048     //AT24C16 2048byte


SerialCommand SCmd;
AH_24Cxx ic_eeprom = AH_24Cxx(AT24C02, BUSADDRESS);

void setup() {  
  Serial.begin(115200); 
  Wire.begin();
  SCmd.addCommand("CHANGE",change);
  Serial.println("Ready"); 
}

void loop() {  
  SCmd.readSerial();
}

void change() {
  char *arg, *pass;
  int len;

  arg = SCmd.next(); 
  len = atoi(arg);
  ic_eeprom.write_byte(100,len);
  delay(100);
  
  pass = SCmd.next();
  for (int i = 1; i<= len; i++) {
    ic_eeprom.write_byte(i,pass[i-1] - '0');
    delay(100);
  }
}

