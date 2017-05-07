#include <SerialCommand.h>

int PIRpin = 8;
int i = 1;
void setup() {
  Serial.begin(115200);
  Serial.println("It's ready'");
  pinMode(PIRpin, INPUT);
}

void loop() {
  int PIR = digitalRead(PIRpin); 
  Serial.print("Test "); 
  Serial.print(i); 
  Serial.println(":");
  if (PIR == HIGH)
    Serial.println("Motion detected ! Motion detected ! Motion detected !");
  else
    Serial.println("No Motion !");
  Serial.println("----------------------");
  i++;
  if (i == 999) i = 1;
  delay(1000);
}




