#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   3
#define CSN_PIN  4

// Define the transmit pipe
const uint64_t pipe = 0xE8E8F0F0E1LL; 
//The "LL" at the end of the constant is "LongLong" type

int VRx = A1;
int VRy = A2;
int button = 2;

int VRx_val, VRy_val;
int power_for_VR = 10;

int light1 = 5;
int light2 = 6;
long long time = 0;

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN);

int data[1];

void setup() {
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(button, INPUT_PULLUP);
  
  /////////////////////////////////////////
  pinMode(power_for_VR, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  
  digitalWrite(light2, HIGH);
  digitalWrite(power_for_VR, HIGH);
  /////////////////////////////////////////
}


void loop() {
  data[0] = 0;

  VRx_val = analogRead(VRx);
  VRy_val = analogRead(VRy);
  while (true) {
    if (up()) {
      data[0] = 1; 
      break;
    }
    if (down()) {
      data[0] = 2; 
      break;
    }
    if (left()) {
      data[0] = 3; 
      break;
    }
    if (right()) {
      data[0] = 4; 
      break;
    }
    if (turn_light()) {
      data[0] = 5; 
      break;
    }
    if (love()) {
      data[0] = 6; 
      break;
    }
    break;
  }
  radio.write(data, sizeof(data));
}

boolean love() {
  if ((VRx_val < 100) and (VRy_val < 100)) return true;
  else return false;
}

boolean up() {
  if ((VRx_val > 275) and (VRx_val < 725) and (VRy_val < 225))
    return true;
  else return false;
}

boolean down() {
  if ((VRx_val > 275) and (VRx_val < 725) and (VRy_val > 775))
    return true;
  else return false;
}

boolean left() {
  if ((VRx_val < 225) and (VRy_val < 725) and (VRy_val > 275))
    return true;
  else return false;
}

boolean right() {
  if ((VRx_val > 775) and (VRy_val > 275) and (VRy_val < 725))
    return true;
  else return false;
}

boolean turn_light() {
  if (digitalRead(button) == LOW) return true; 
  else return false;
}




