#include <SerialCommand.h>

SerialCommand SCmd;

void setup() {
  Serial.begin(9600); 

  SCmd.addCommand("COMMAND",COMMAND); 
  SCmd.addDefaultHandler(unrecognized);
  Serial.println("Ready !"); 

}

void loop() {  
  SCmd.readSerial();     // We don't do much, just process serial commands
}


void COMMAND() {
  char *arg;
  int num;

  arg = SCmd.next();
  num = atoi(arg);
  Serial.println(arg);
  Serial.println(num);
  Serial.println();
}

void unrecognized() {

}


