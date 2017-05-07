#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
int data[1];
RF24 radio(CE_PIN, CSN_PIN);

// Define the transmit pipe
const uint64_t pipe = 0xE8E8F0F0E1LL;

const int constRain = 450;
const int rainToNoRain = 300;
int adc = A0;
unsigned long timer = 0;
const int delayTime = 50;
boolean rainning = false,lastRainning = false;
unsigned long i = 0,maxPoint,minPoint,value;
int countCheckTimes = 100;
void setup() {

  maxPoint = minPoint = value = analogRead(adc);

  radio.begin();
  radio.openWritingPipe(pipe);
  data[0] = 0;

}
void loop() {
  if (millis() - timer > delayTime) {
    value = analogRead(adc);
    if (rainning) {
      i = (i+1) % countCheckTimes;
      if (i == 1) 
        maxPoint = minPoint;
      else 
        maxPoint += long(analogRead(adc));
      //Serial.print(minPoint);
      //Serial.print(" ");
      //Serial.println(analogRead(adc));

      if (i == 0) {      
        minPoint = min(minPoint,498); 
        maxPoint /= long (countCheckTimes);
        if (maxPoint > (500-minPoint)*0.75 && maxPoint > minPoint) {
          minPoint = maxPoint = analogRead(adc);
          rainning = false;
        }
      }
    } 
    else {
      maxPoint = max(maxPoint, analogRead(adc));
      minPoint = min(minPoint, analogRead(adc));
      if ((maxPoint - minPoint > constRain - (maxPoint <= 550)*0.35*maxPoint ) || (maxPoint < 300 && maxPoint - minPoint >= 50)) {
        rainning = true; 
        timer = millis() + 10000 - delayTime;
      }
    }
    if (analogRead(adc) >= 1020) {
      rainning = false;
    }
    if (rainning xor lastRainning) {
      //Serial.print(" Mua: ");
      //Serial.println(rainning);
      data[0] = 1;
      radio.write(data, sizeof(data));
    }
    lastRainning = rainning;
    timer = millis();
  } 
  else {
    data[0] = 0;
    radio.write(data, sizeof(data));
  }
}

