#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Please wait ...");
  delay(15000);
  lcd.clear();
  lcd.print("Reading:");
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print("       ");  
  lcd.setCursor(0,1);
  lcd.print(analogRead(A0));
  delay(500);
}
