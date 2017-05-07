#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
long data,id,value;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready !");
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    data = mySwitch.getReceivedValue();
    id = data >> (24-4);
    value = (data >> (24-14)) % 1024;
    Serial.println(id);
    Serial.println(value);
    Serial.println(data,BIN);
    Serial.println();
    Serial.println();

    mySwitch.resetAvailable();
  }

  delay(1500);
}
