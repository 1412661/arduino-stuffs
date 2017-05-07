#include <SerialCommand.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SerialCommand SCmd;

char str1[255] = "Hello";
char str2[255] = "Hello";


void setup() {
  Serial.begin(115200); 

  SCmd.addCommand("lcd1",lcd1); 
  SCmd.addCommand("lcd2",lcd2); 
  SCmd.addDefaultHandler(unrecognized);
  //strcpy(str1,"Hello");
  //strcpy(str2,"Hello");
  lcd.init();
  lcd.backlight();
  lcd.print("WELCOME ...");
  delay(2000);
}

void loop() {  
  SCmd.readSerial();
  delay(500);

  lcd.clear();
  lcd.print(str1);
  lcd.setCursor(0,1);
  lcd.print(str2);
  if (max_len(str1,str2) > 16) {
    delay(500);
    for (int i = 1; i<=(max_len(str1,str2)-16); i++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
  }
}


void lcd1() {
  char* arg = SCmd.next();
  if (arg != NULL) strcpy(str1,arg);
}

void lcd2() { 
  char* arg = SCmd.next();
  if (arg != NULL) strcpy(str2,arg);
}

int max_len(char s1[255], char s2[255]) {
  if (strlen(s1) > strlen(s2)) return strlen(s1);
  else return strlen(s2);
}

void unrecognized() {
}











