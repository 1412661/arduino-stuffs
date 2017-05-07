#include <DHT.h>
#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9);
#define DHTPIN 2

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Nhiet do: ");  //10
  lcd.setCursor(0,1);
  lcd.print("Do am: "); //7
  lcd.createChar(1, degree);

  dht.begin();  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
  } 
  else {
    lcd.setCursor(10,0);
    lcd.print(round(t));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(h));
    lcd.print(" %");    
  }
}


