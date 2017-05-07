#include <RCSwitch.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
RCSwitch mySwitch = RCSwitch();

long long data = 0;
long id = 4,doam,nhietdo; //sensor id

void setup() {
  mySwitch.enableTransmit(10); //pin 10
  dht.begin();
}

void loop() {
  doam = round(dht.readHumidity());
  nhietdo = round(dht.readTemperature());

  data = 0B000000000000000000000000;
  data = data | (id << 20);
  data = data | (nhietdo << 10);
  data = data | doam;

  mySwitch.send(data,24);
  
  delay(60000);
}



