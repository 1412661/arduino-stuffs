#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  long value = mySwitch.getReceivedValue();
  if (value != 0) {
    Serial.println(value);
    delay(100);   
  }
  mySwitch.resetAvailable();
  delay(1);
}






