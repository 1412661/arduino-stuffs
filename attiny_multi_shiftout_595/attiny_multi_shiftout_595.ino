/* Note: 
 This code is written for Attiny13A-PU for shiftout to multi SN74HC595N
 */

#define isON(S,i) (S & (1 << i))

/* Configuration */
//Pin connected to ST_CP (pin 12) of 74HC595
byte latchPin = 1;
//Pin connected to SH_CP (pin 11) of 74HC595
byte clockPin = 2;
//Pin connected to DS (pin 14) of 74HC595
byte dataPin = 0;
//Number of 8-bit shiftout
byte bits = 2;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  turn(0B0111001001011011,0);
}

void turn(word data, word de) {
  digitalWrite(latchPin, LOW);
  byte out;
  for (byte k = bits; k > 0; k--) {
    out = 0;
    for (byte i = 0; i<= 7; i++) {
      if (isON(data,i+(k-1)*8)) {
        word P = 1;
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

