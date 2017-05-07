#include <SPI.h>
#include <LiquidCrystal.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
LiquidCrystal lcd(9);
long long data,t;
int b1,b2,b3;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  mySwitch.enableReceive(0); //pin 2
}

void loop() {

  data = mySwitch.getReceivedValue();
  if (data != 0) {
    lcd.clear();
    b1 = data >> 20;
    b2 = (data >> 10) % 1024;
    t = b1 << 20;
    t |= b2 << 10;
    b3 = data - t;
    int ccc = data >> 20;
    lcd.print(ccc);
    lcd.print(' ');
    lcd.print(b2);
    lcd.print(' ');
    lcd.print(b3);
    lcd.setCursor(0,1);
    lcd.print("Bit length: ");
    lcd.print(mySwitch.getReceivedBitlength());
  }

  delay(10);

}









