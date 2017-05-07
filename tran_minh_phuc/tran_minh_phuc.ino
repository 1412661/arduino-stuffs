/* Note: 
 This code is written for Attiny13A-PU for shiftout to SN74HC595N
 */
#define isON(S,i) (S & (1 << i))

/* Configuration */
//Pin connected to ST_CP (pin 12) of 74HC595
byte latchPin = 1;
//Pin connected to SH_CP (pin 11) of 74HC595
byte clockPin = 2;
////Pin connected to DS (pin 14) of 74HC595
byte dataPin = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  word S = 0;   
  byte i,c,a = 0;

  while (true) {
    for (i = 16; i > a; i--) {
      turn(bitON(S,i-1), 100);
    }
    S = bitON(S,a);
    a++;

    if (a == 16) {
      break;
    }
  }

  delay(500);

  turn(65535,250);
  S = 0B1010101010101010;
  for (c = 1; c<=40; c++) {
    turn(S,100);
    S = ~S; 
  }
  turn(0,500);

  for (c = 1; c<=12; c++) {
    if (c % 2 == 0) {
      turn(65535, 350);
    } 
    else {
      turn(0, 350); 
    }
  }
  delay(1000);

  S = 65535;
  turn(S,700);

  a = 7;
  c = 8;
  while (true) {
    S = bitOFF(S,a);
    S = bitOFF(S,c);
    turn(S, 200);
    a = a - 1;
    c = c + 1;
    if ((a == 0) and (c == 15)) {
      turn(0, 1000);
      break; 
    }
  }
}

void turn(word data, word de) {
  byte bits = 2;
  digitalWrite(latchPin, LOW);
  byte out;
  for (byte k = bits; k > 0; k--) {
    out = 0;
    for (byte i = 0; i<= 7; i++) {
      if (isON(data,i+(k-1)*8)) {
        byte P = 1;
        for(byte c = 1; c<=i; c++) {
          P = 2 * P;
        }
        out += P;
      }
    }
    shiftOut(dataPin, clockPin, out);
  }

  digitalWrite(latchPin, HIGH);
  delay(de);
}

void shiftOut(byte myDataPin, byte myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first
  byte pinState;

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (byte i = 8; i > 0; i--)  {
    digitalWrite(myClockPin, 0);

    if (isON(myDataOut,i-1)) {
      pinState = 1;
    }
    else {	
      pinState = 0;
    }

    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }

  digitalWrite(myClockPin, 0);
}

word bitON(word data, byte i) {
  return (data | (1 << i));
}

word bitOFF(word data, byte i) {
  return (data &= ~(1 << i));
}


