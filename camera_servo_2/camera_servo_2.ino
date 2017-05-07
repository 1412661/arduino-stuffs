#include <RCSwitch.h>
#include <SerialCommand.h>
#include <Servo.h> 
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;


#define _GSM_TXPIN_ 2
#define _GSM_RXPIN_ 3

int led = 13;

SerialCommand SCmd;
Servo servo1;
Servo servo2;
RCSwitch mySwitch = RCSwitch();
unsigned long long mili;
boolean sStatus=true;
void setup() {  
  mili = 0;
  servo1.attach(5,0,180);
  servo2.attach(6,0,180);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  SCmd.addCommand("S",change);
  SCmd.addCommand("SEND_315",send_315); 
  SCmd.addCommand("GSM_SEND",gsm_send);   
  SCmd.addDefaultHandler(unrecognized); 
  servo_center();
  mySwitch.enableTransmit(10);
  
  if (gsm.begin(2400)) {
    Serial.println("GSM_OK");
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
    Serial.println("GSM_FAILED");
  }
}

void loop() {  
  SCmd.readSerial();  
  if (sStatus && millis() - mili >= 2000) {
    sStatus = false;
    servo1.detach();
    servo2.detach();
    mili=millis();
  }
}


void change()   {
  int deg1,deg2;  
  if (!sStatus) {
    servo1.attach(5);
    servo2.attach(6);
  }
  mili = millis();
  sStatus=false;
  deg1=atol(SCmd.next()); 
  deg2=atol(SCmd.next());
  servo1.write(deg1);
  servo2.write(deg2);
  
}

void servo_center() {
  servo1.write(90);
  servo2.write(90); 
}

void send_315() {
  char *arg;
  long val_315;

  arg = SCmd.next();
  val_315 = atol(arg); 

  mySwitch.send(val_315, 24);
  delay(100);
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





