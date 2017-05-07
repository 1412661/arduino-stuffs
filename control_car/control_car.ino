// Demo Code for SerialCommand Library
// Steven Cogswell
// May 2011

#include <SerialCommand.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


SerialCommand SCmd;   // The demo SerialCommand object

void setup()
{  
  
  Serial.begin(9600); 

  // Setup callbacks for SerialCommand commands 
  SCmd.addCommand("UP",up);       // Turns LED on
  SCmd.addCommand("DOWN",down);        // Turns LED off
  SCmd.addCommand("LEFT",left);     // Echos the string argument back
  SCmd.addCommand("RIGHT",right);  // Converts two arguments to integers and echos them back 
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 
   mySwitch.enableTransmit(10);

  Serial.println("Ready"); 

}

void loop()
{  
  SCmd.readSerial();     // We don't do much, just process serial commands
}

void up() {
 mySwitch.send(0B000000000000110011001100,24); 
}

void down() {
 mySwitch.send(0B000000000000110000110011,24); 
}

void left() {
 mySwitch.send(0B000000000000110011000011,24); 
}

void right() {
 mySwitch.send(0B000000000000110000111100,24); 
}


// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
  
  
}

