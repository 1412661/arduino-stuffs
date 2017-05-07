//Remote control
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN); 
const uint64_t pipe = 0xE8E8F0F0E1LL;

int data[1];
int dc1[2] = {
  2,3};
int dc2[2] = {
  4,5};

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  pinMode(dc1[0], OUTPUT);
  pinMode(dc1[1], OUTPUT);
  pinMode(dc2[0], OUTPUT);
  pinMode(dc2[1], OUTPUT);
}


void loop() {
  if (radio.available()) {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done) {
      // Fetch the data payload      
      done = radio.read(data, sizeof(data));

      if (data[0] != 5) {
        Serial.print("RECEIVE ");
        Serial.println(data[0]);
      }
      delay(30);
      switch (data[0]) {
      case 0:
        hold();
        break;
      case 1:
        up(); 
        break;
      case 2:
        down(); 
        break;
      case 3:
        left(); 
        break;
      case 4:
        right(); 
        break;
      case 5:
        Serial.println("LIGHT");
        break;
      case 6:
        hold();
        delay(1000);
        break;
      }
    }
  }
  else {
    Serial.println("DISCONNECT");
    delay(100);
  }
  delay(1);
}

void up() {
  digitalWrite(dc1[0], HIGH);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], HIGH);
  digitalWrite(dc2[1], LOW);
}

void down() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], HIGH);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], HIGH);
}

void right() {
  digitalWrite(dc1[0], HIGH);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], HIGH);
}

void left() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], HIGH);
  digitalWrite(dc2[0], HIGH);
  digitalWrite(dc2[1], LOW);
}

void hold() {
  digitalWrite(dc1[0], LOW);
  digitalWrite(dc1[1], LOW);
  digitalWrite(dc2[0], LOW);
  digitalWrite(dc2[1], LOW);
}









