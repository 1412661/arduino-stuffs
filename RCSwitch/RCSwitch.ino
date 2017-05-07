
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

long data;

void setup() {

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);

}

void loop() {

  data = 0B000000000000110011111111;
  mySwitch.send(data,24);
  delay(1000);
  
  data = 0B000000000000110000000000;
  mySwitch.send(data,24);
  delay(1000);

}

