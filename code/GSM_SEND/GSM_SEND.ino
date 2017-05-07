#include <SerialCommand.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;


#define _GSM_TXPIN_ 2
#define _GSM_RXPIN_ 3

int led = 13;
SerialCommand SCmd;   // The demo SerialCommand object

void setup() {  
  pinMode(led, OUTPUT);
  Serial.begin(115200); 
  Serial.println("GSM_STARTING");

  if (gsm.begin(2400)) {
    Serial.println("GSM_OK");
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
    Serial.println("GSM_FAILED");
  }

  SCmd.addCommand("GSM_SEND",gsm_send);    
  SCmd.addDefaultHandler(unrecognized);
}

void loop() {  
  SCmd.readSerial();
}

void gsm_send() { 
  digitalWrite(led, LOW);
  
  char *c1, *c2;
  c1 = SCmd.next();
  c2 = SCmd.next();

  if (sms.SendSMS(c1, c2)) {
    digitalWrite(led, HIGH);

    Serial.println("GSM_SMS_SENT");

  }
  else   Serial.println("GSM_SMS_FAILED");
}

void unrecognized() {
}














