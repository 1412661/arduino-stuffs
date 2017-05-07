#define isON(S,i) (S & (1 << i))


//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  word S = 0;
  turn(S,250);
  for (int i = 0; i <= 15; i++) {
     S = bitON(S,i);
     turn(S,250);
  }
  delay(500);
  for (int i = 0; i <= 15; i++) {
     S = bitOFF(S,i);
     turn(S,250);
  }
}

void turn(word data, int de) {
  int bits = 2;
  digitalWrite(latchPin, LOW);
  byte out;
  for (int k = bits-1; k >=0; k--) {
    out = 0;
    for (int i = 0; i<= 7; i++) {
      if (isON(data,i+k*8)) {
        out += luythua(i);
      }
    }
    shiftOut(dataPin, clockPin, MSBFIRST, out);
  }

  digitalWrite(latchPin, HIGH);
  delay(de);
}

word bitON(word S, int i) {
  return (S | (1 << i));
}

word bitOFF(word S, int i) {
   return (S &= ~(1 << i));
}

int luythua(int lt) {
  int P = 1;
  for(int i = 1; i<=lt; i++) {
    P = 2 * P;
  }

  return P;
}
