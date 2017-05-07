#include <SPI.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(10);

byte degree[8] = {
  0B00111,
  0B00101,
  0B00111,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() { 
  sensors.begin();
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
}

void loop() {
  sensors.requestTemperatures();
  lcd.clear();
  lcd.print("Nhiet do:");
  lcd.setCursor(0,1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.write(1);
  lcd.print("C");
  delay(300);
}


