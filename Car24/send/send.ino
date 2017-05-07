#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

// Define the transmit pipe
const uint64_t pipe = 0xE8E8F0F0E1LL; 
//The "LL" at the end of the constant is "LongLong" type

int control[5] = {
  2,3,4,5,6
}; //up down left right light


// Create a Radio
RF24 radio(CE_PIN, CSN_PIN);

int data[1];

void setup() {
  radio.begin();
  radio.openWritingPipe(pipe);

  for (int i=0; i<=4; i++)
    pinMode(control[i], INPUT_PULLUP);
}


void loop() {
  data[0] = 0;
  for (int i = 1; i<=5; i++) {
    if (digitalRead(control[i-1]) == LOW) {
      data[0] = i;
      break;
    }
  }
  if ((digitalRead(control[0]) == LOW) 
    and (digitalRead(control[1]) == LOW)) data[0] = 6;
  radio.write(data, sizeof(data));
}

