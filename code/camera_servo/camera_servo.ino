#include <RCSwitch.h>
#include <SerialCommand.h>
#include <Servo.h> 

SerialCommand SCmd;   // The demo SerialCommand object
Servo servo1;
Servo servo2;
RCSwitch mySwitch = RCSwitch();

void setup()
{  
  servo1.attach(5,0,180);
  servo2.attach(6,0,180);

  Serial.begin(115200);
  SCmd.addCommand("SERVO1",servo11);  // Converts two arguments to integers and echos them back 
  SCmd.addCommand("SERVO2",servo22);  // Converts two arguments to integers and echos them back 

  SCmd.addCommand("SERVO_CENTER",servo_center);  // Converts two arguments to integers and echos them back 
  SCmd.addCommand("SEND_315",send_315); 
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 
  servo_center();
  mySwitch.enableTransmit(10);
}

void loop()
{  
  SCmd.readSerial();     // We don't do much, just process serial commands
}


void servo11()    
{
  int deg,cdeg;  
  char *arg; 

  arg = SCmd.next(); 
  deg=atol(arg); 
  cdeg = servo1.read();

  if (((deg + cdeg) > 0) && ((deg + cdeg) < 180)) {
    servo1.write(servo1.read() + deg);
    Serial.println("OK");
    delay(100);
  }
}

void servo22()    
{
  int deg,cdeg;  
  char *arg; 

  arg = SCmd.next(); 
  deg=atol(arg); 
  cdeg = servo2.read();

  if (((deg + cdeg) > 0) && ((deg + cdeg) < 180)) {
    servo2.write(servo2.read() + deg);
    delay(100);  
    Serial.println("OK");
  }
}

void servo_center() {
  servo1.write(90);
  servo2.write(90); 
  Serial.println("OK");
}

void send_315() {
  char *arg;
  long val_315;

  arg = SCmd.next();
  val_315 = atol(arg); 
  
  mySwitch.send(val_315, 24);
}
// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
}

