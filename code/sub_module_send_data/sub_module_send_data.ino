#include <RCSwitch.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
RCSwitch mySwitch = RCSwitch();

unsigned long time;
long long data;
const int t = 1; //time to send
const int id = 1;

void setup() {
  mySwitch.enableTransmit(10); //pin 10
  dht.begin();
}

void loop() {
  byte ctime = gettime(millis());

  if (ctime == t) {
    int h = round(dht.readHumidity());
    int t = round(dht.readTemperature());
    data = 0B000000000000000000000000;
    data = id << (24-4);
    data |= t << (24-4-10);
    data |= h << (24-4-10-10);
    mySwitch.send(data,24);
  }

  delay(1000);
}

byte gettime(unsigned long data) {
  data = round(data/1000);
  while (data > 10) {
    data = data % 10;
  } 

  return data;
}


