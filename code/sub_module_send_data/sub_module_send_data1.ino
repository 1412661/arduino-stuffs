unsigned long time;

const byte t = 4;
byte ctime;
boolean s = true;

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

}

void loop() {
  ctime = gettime(millis());

  if (ctime == t) {
    if (s) mySwitch.send(15,24);
    else mySwitch.send(20,24);
    s = not s;
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

