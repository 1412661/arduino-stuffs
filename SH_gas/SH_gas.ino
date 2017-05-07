#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

int read_ = 3;
long id = 3, val;


void setup() {
  mySwitch.enableTransmit(10);
  delay(21000);
  pinMode(read_, INPUT_PULLUP);
  val = id << 20;

}

void loop() {
  if (digitalRead(read_) == LOW) {
    mySwitch.send(val | (1 << 19),24);
  } 
  else {
    mySwitch.send(val, 24);
  }

  delay(40000);
}





