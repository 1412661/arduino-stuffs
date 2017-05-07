#include <RCSwitch.h>
#include <NewPing.h>

RCSwitch mySwitch = RCSwitch();

#define TRIGGER_PIN  7
#define ECHO_PIN     6
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int attiny = 9;
long val;
long id = 7;
int sonic_detect = 30;

int pir = 8;

int debug_pir = 3;
int debug_sonic = 4;

void setup() {
  mySwitch.enableTransmit(10);
  val = (id << 20) | (1 << 19);
  pinMode(attiny, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(debug_pir, OUTPUT);
  pinMode(debug_sonic, OUTPUT);
  delay(5000);
}

void loop() {
  delay(50);
  
  digitalWrite(debug_pir, LOW);
  digitalWrite(debug_sonic, LOW);
  
  delay(50);
  unsigned int uS = sonar.ping();
  int sonic = uS / US_ROUNDTRIP_CM;
  int motion = digitalRead(pir);
  if ((motion) | ((sonic < sonic_detect) && (sonic != 0))) {
    digitalWrite(attiny, HIGH);
    mySwitch.send(val and (1 << 19),24);
    delay(2000);
  } else {
    mySwitch.send(val,24);
    delay(500);
  }
  digitalWrite(attiny, LOW);

  digitalWrite(debug_pir, motion);
  digitalWrite(debug_sonic, ((sonic < sonic_detect) && (sonic != 0)));

  delay(10);
}



