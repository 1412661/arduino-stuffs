int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

byte N[] = {
  0B00000011,  //0
  0B10011111,  //1
  0B00100101,  //2
  0B00001101,  //3
  0B10011001,  //4
  0B01001001,  //5
  0B01000001,  //6
  0B00011111,  //7
  0B00000001,  //8
  0B00001001  //9
};

byte i;

byte led[] = {
  2,3,4};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
}



void loop() {
  for (i = 1; i<=3; i++) {
    if (i==1) turn(1,0,0);
    if (i==2) turn(0,1,0);
    if (i==3) turn(0,0,1);
    delay(7);
  }
}

void turn(byte a, byte b, byte c) {
  digitalWrite(latchPin, LOW);
  digitalWrite(led[0], a);
  digitalWrite(led[1], b);
  digitalWrite(led[2], c);
  shiftOut(dataPin, clockPin, LSBFIRST, N[i]);  
  digitalWrite(latchPin, HIGH);
}




