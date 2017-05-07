//#include <RCSwitch.h>

//RCSwitch mySwitch = RCSwitch();

long data,sensor,id = 15;

void setup() {
  Serial.begin(9600);
  //mySwitch.enableTransmit(10);
}

void loop() {
  sensor = analogRead(A0);
  data = id << (24-4);
  data |= sensor << (24-14);
  Serial.println(data,BIN);
  Serial.println(sensor);
  Serial.println("-----------------------");
  id = data >> (24-4);
  sensor = (data >> (24-14)) % 1024;
  Serial.println(id);
  Serial.println(sensor);
  Serial.println();
  Serial.println();
  delay(1500);
  //mySwitch.send(5393, 24);
}

