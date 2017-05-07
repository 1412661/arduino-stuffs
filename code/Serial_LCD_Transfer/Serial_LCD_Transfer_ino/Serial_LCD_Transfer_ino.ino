
#include <Keypad.h>
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char alphaKeys[ROWS][COLS] = {
  {
    '#','0','*'    }
  ,
  {
    '9','8','7'    }
  ,
  {
    '6','5','4'    }
  ,
  {
    '3','2','1'    }
};

long long val;
int id = 1;

byte rowPins[ROWS] = {
  3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(alphaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(115200);
  mySwitch.enableReceive(0);
}

void loop(){
  char customKey = customKeypad.getKey();

  if (customKey){
    switch (customKey) {
    case '0': 
      Serial.println("PUSH 0"); 
      break;
    case '1': 
      Serial.println("PUSH 1"); 
      break;
    case '2': 
      Serial.println("PUSH 2"); 
      break;
    case '3': 
      Serial.println("PUSH 3"); 
      break;
    case '4': 
      Serial.println("PUSH 4"); 
      break;
    case '5': 
      Serial.println("PUSH 5"); 
      break;
    case '6': 
      Serial.println("PUSH 6"); 
      break;
    case '7': 
      Serial.println("PUSH 7"); 
      break;
    case '8': 
      Serial.println("PUSH 8"); 
      break;
    case '9': 
      Serial.println("PUSH 9"); 
      break;
    case '*': 
      Serial.println("ENTER"); 
      break;
    case '#': 
      Serial.println("CLEAR"); 
      break;
    }
    delay(50);
  }

  
    val = mySwitch.getReceivedValue();
    if ((val != 0) and ((val >> 20) == id)) { 
      if (val == 1572864) Serial.println("OPEN"); //0B000110000000000000000000
      if (val == 1310720) Serial.println("CLOSE");  //0B000101000000000000000000
      
      //0B000111000000000000000000
      if ((val >> 18) == 7) {
        long pass = val - 0B000111000000000000000000;
        Serial.print("CHANGE ");
        Serial.println(pass);
      }
      delay(5);
      mySwitch.resetAvailable();
      delay(1000);
    }
  

  delay(10);
}


