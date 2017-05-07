#include <SerialCommand.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
#define _GSM_TXPIN_ 3
#define _GSM_RXPIN_ 4

SerialCommand SCmd;   // The demo SerialCommand object

char smsbuffer[160];
char n[20];

void setup()
{  
  Serial.begin(115200); 
  Serial.println("GSM_STARTING");
  if (gsm.begin(2400))
    Serial.println("GSM_OK");
  else Serial.println("GSM_FAILED");
  SCmd.addCommand("GSM_SEND",gsm_send);     
  SCmd.addCommand("GSM_CHECK",gsm_check); 
  SCmd.addDefaultHandler(unrecognized);
  clear_sms();
}

void loop() {  
  SCmd.readSerial();
  delay(1000);
  gsm_check();
}

void gsm_send() { 
  char *c1, *c2;
  c1 = SCmd.next();
  c2 = SCmd.next();

  if (sms.SendSMS(c1, c2))
    Serial.println("GSM_SMS_SENT");
  else   Serial.println("GSM_SMS_FAILED");

}

void gsm_check() {
  /*if (gsm.readSMS(smsbuffer, 160, n, 20))
   {
   Serial.print("GSM_SMS ");
   Serial.print(n);
   Serial.print(" CONTENTS ");
   Serial.println(smsbuffer);
   }
   else Serial.println("GSM_NO_SMS");*/
  char phone_num[20]; // array for the phone number string
  char sms_text[100]; // array for the SMS text string

  for (int i = 1; i<= 20; i++) {
    sms.GetSMS(i, phone_num, sms_text, 100);
    Serial.print(phone_num);
    Serial.print(" ");
    Serial.println(sms_text);

    delay(100); 
  }
}

void unrecognized() {
}

void clear_sms() {
  delay(500);
  for (int i = 1; i<= 20; i++) {
    Serial.println((int)sms.DeleteSMS(i));
    delay(500);
  }
}













