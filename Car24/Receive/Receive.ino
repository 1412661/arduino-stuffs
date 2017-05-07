//Remote control
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN); 
const uint64_t pipe = 0xE8E8F0F0E1LL;

//LCD display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

int data[1];
int dc1[2] = {
  2,3};
int dc2[2] = {
  4,5};
int light = 7;
boolean light_status;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  lcd.init();
  lcd.backlight();
  lcd.print("CAR24 Project");
  lcd.setCursor(0,1);
  lcd.print("  Let's enjoy :D");
  delay(3000);

  light_status = false;

  pinMode(dc1[0], OUTPUT);
  pinMode(dc1[1], OUTPUT);
  pinMode(dc2[0], OUTPUT);
  pinMode(dc2[1], OUTPUT);
  pinMode(light, OUTPUT);
}


void loop() {
  if (radio.available()) {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done) {
      // Fetch the data payload      
      done = radio.read(data, sizeof(data));

      lcd.clear();
      lcd.print("Nhan du lieu: ");
      if (data[0] != 6) lcd.print(data[0]);
      lcd.setCursor(0,1);

      switch (data[0]) {
      case 0:
        hold();
        break;
      case 1: 
        up(); 
        break;
      case 2: 
        down(); 
        break;
      case 3: 
        left(); 
        break;
      case 4: 
        right(); 
        break;
      case 5:
        light_status = !light_status;
        digitalWrite(light, light_status);
        break;
      case 6:
        //hold
        digitalWrite(dc1[0], LOW);
        digitalWrite(dc1[1], LOW);
        digitalWrite(dc2[0], LOW);
        digitalWrite(dc2[1], LOW);

        lcd.setCursor(0,0);
        lcd.print("   I LOVE YOU   ");
        lcd.setCursor(0,1);
        lcd.print(" Smile and Love ");
        delay(200);
        break;
      }
      delay(1);
    }
  }
  else {
    lcd.clear();
    lcd.print("Mat ket noi !");
    delay(200);
  }
  delay(1);
}

void up() {
  digitalWrite(dc1[0], HIGH);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], HIGH);
  digitalWrite(dc2[1], LOW);

  lcd.print("Tien len");
}

void down() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], HIGH);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], HIGH);

  lcd.print("Lui lai");
}

void right() {
  digitalWrite(dc1[0], HIGH);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], HIGH);

  lcd.print("Qua phai");
}

void left() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], HIGH);
  digitalWrite(dc2[0], HIGH);
  digitalWrite(dc2[1], LOW);

  lcd.print("Qua trai");
}

void hold() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], LOW);
  lcd.print("Dung lai .....");
}





