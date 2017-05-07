#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10);

byte heart[8] = {
  0B00000,
  0B01010,
  0B11111,
  0B11111,
  0B11111,
  0B01110,
  0B00100,
  0B00000
};

byte _[8] = {
  0,0,0,0,0,0,0,31};

byte c = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, heart);
  lcd.createChar(2, _);

  pinMode(2, INPUT_PULLUP);
}

void loop() {

  if ((digitalRead(2) == LOW) and (c != 1)) {
    mess1();
    delay(5000);
    mess2();  
    delay(5000);
    mess3();
    delay(5000);
    mess4();  
    delay(5000);
    c = 1;
  }

  index();

  delay(200);
}

void index() {
  lcd.setCursor(0,0);
  lcd.write(2);
  lcd.write(2);
  lcd.write(2);
  lcd.print("I LOVE YOU");
  lcd.write(2);
  lcd.write(2);
  lcd.write(2);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(500);
  lcd.setCursor(0, 1);
  for (int i=1;i<=16;i++) {
    lcd.write(1);
    delay(500);
  }
}

void mess1() {
  lcd.setCursor(0, 0);
  lcd.print("You are so      ");
  lcd.setCursor(0, 1);
  lcd.print("     beautiful !"); 
}

void mess2() {
  lcd.setCursor(0, 0);
  lcd.print("Really, not lie");
  lcd.setCursor(0, 1);
  lcd.print("                "); 
}

void mess3() {
  lcd.setCursor(0, 0);
  lcd.print("I think...      ");
  lcd.setCursor(0, 1);
  lcd.print(" you are smiling"); 
}

void mess4() {
  lcd.setCursor(0, 0);
  lcd.print("Just simple ... ");
  lcd.setCursor(0, 1);
  lcd.print("I'll show you .."); 
}





