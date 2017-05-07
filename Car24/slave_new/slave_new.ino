#include <SerialCommand.h>
SerialCommand SCmd; 

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
#define DHT_VCC 5
#define DHT_GND 4
DHT dht(DHTPIN, DHTTYPE);

int power = A0;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

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

boolean light_status = false;
int light_ = 3;
int buzzer = 4;
long time;

void setup() {
  Serial.begin(115200);
  dht_power();
  delay(5);
  dht.begin();

  pinMode(light_, OUTPUT);
  pinMode(buzzer, OUTPUT);
  SCmd.addCommand("RECEIVE",receive_data);    
  SCmd.addCommand("DISCONNECT",disconnect); 
  SCmd.addCommand("LIGHT",turn_light);  
  SCmd.addDefaultHandler(unrecognized);

  lcd.init();
  lcd.backlight();
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print("   CAR24 Project");
  lcd.createChar(1, degree);
  delay(2000);
  time = millis();
}

void loop() {    
  int h = round(dht.readHumidity());
  int t = round(dht.readTemperature());
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.write(1);
  lcd.print("C ");
  lcd.print(h);
  lcd.print("%   ");
  lcd.print(analogRead(power)/1024.0*5.0);
  lcd.print("V");

  SCmd.readSerial();
  delay(25);
  SCmd.clearBuffer();
}

void receive_data() {
  int data = atoi(SCmd.next());
  if (data != 6) {
    lcd.setCursor(0,0);
    lcd.print("Nhan du lieu: ");
    lcd.print(data);
    lcd.print("  ");    
  }
  else love();  
}

void turn_light() {
  if ((millis() - time) >= 1000) {
    light_status = !light_status;
    digitalWrite(light_, light_status);
    lcd.setCursor(0,0);
    if (light_status)
      lcd.print("Da bat den      ");
    else lcd.print("Da tat den      ");
    time = millis();
    buzz(150);
    buzz(150);
    buzz(150);
  }
}
void love() {
  lcd.clear();
  lcd.print("   I LOVE YOU"   );
  lcd.setCursor(0,1);
  lcd.print(" Smile and Love ");
  delay(1000);
  lcd.clear();
}

void disconnect() {
  lcd.setCursor(0,0);
  lcd.print("Mat ket noi !   ");
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized() {
}

void dht_power() {
  pinMode(DHT_VCC, OUTPUT);
  pinMode(DHT_GND, OUTPUT);
  digitalWrite(DHT_VCC, HIGH);
  digitalWrite(DHT_GND, LOW);
}

void buzz(int de) {
  digitalWrite(buzzer, HIGH);
  delay(de);
  digitalWrite(buzzer, LOW);
  delay(de);
}














