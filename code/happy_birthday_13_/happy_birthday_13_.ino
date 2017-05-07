/*
  ARDUINO SHIFTOUT 13 BITS TO 2 HC595
 */

#define isON(S,i) (S & (1 << i))


//Pin connected to latch pin (ST_CP) of 74HC595
const byte latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const byte clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const byte dataPin = 11;
const float timer = 0.5;
word hpbd[] = {
  0B0000000011111, 
  0B0001111100000, 
  0B1110000000000
};


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  turn(0B1111111111111,2000);
  turn(0,600);
}

void loop() {
  word S = 0;   
  byte i,c,a = 0;

  while (true) {
    for (i = 13; i > a; i--) {
      turn(bitON(S,i-1), 100);
    }
    S = bitON(S,a);
    a++;

    if (a == 13) {
      break; 
    }
  }
  delay_(500);
  turn(0B1111111111111,250);
  S = 0B1010101010101;
  for (c = 1; c<=40; c++) {
    turn(S,100);
    S = ~S; 
  }
  turn(0,500);
  for (c = 1; c <= 4; c++) {
    S = 0;
    for (i = 0; i <= 2; i++) {
      S = S | hpbd[i];
      turn(S,600);
    }
    turn(0, 380);
  }

  for (c = 1; c<=12; c++) {
    if (c % 2 == 0) {
      turn(0B1111111111111, 350);
    } 
    else {
      turn(0, 350); 
    }
  }
  delay_(1000);

  S = 0B1111111111111;
  turn(S,1200);

  //deal many memory
  while (S != 0) {
    a = round(rand() / 2730.5833);
    if (isON(S,a)) {
      S = bitOFF(S,a);
      turn(S,1200); 
    }
  }
  delay_(1500);

}

void turn(word data, word de) {
  digitalWrite(latchPin, LOW);
  byte out;
  out = 0;
  for (byte i = 8; i<=12; i++) {
    if (isON(data,i)) {
      out += luythua(i-8);
    }
  }
  shiftOut(dataPin, clockPin, MSBFIRST, out);

  out = 0;
  for (byte i = 0; i<= 7; i++) {
    if (isON(data,i)) {
      out += luythua(i);
    }
  }
  shiftOut(dataPin, clockPin, MSBFIRST, out);

  digitalWrite(latchPin, HIGH);

  delay_(de);
}

word bitON(word S, byte i) {
  return (S | (1 << i));
}

word bitOFF(word S, byte i) {
  return (S &= ~(1 << i));
}

int luythua(byte lt) {
  byte P = 1;
  for(byte i = 1; i<=lt; i++) {
    P = 2 * P;
  }

  return P;
}

void delay_(word de) {
  delay(de/timer); 
}
