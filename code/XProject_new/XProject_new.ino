#define GetBit(S, i) (S & (1 << i))
#define bitON(S, i) (S | (1 << i))
#define bitOFF(S, i) (S &= ~(1 << i))

int c = 14;

int leds[] = {
  2,3,4,5,6,7,8,9,10,11,12,13,A0,A1};

int t = 100;
int bits = 0;

void setup() {
  for (int i = 0; i<=c-1;i++) pinMode(leds[i], OUTPUT);
  delay(500);
}

void loop() {
  //bits = 0B11111111111111;
  //turn(0,t*5);
  //turn(0B11111111111111,t*5);
  for (int i = 0; i<=c-1;i++) digitalWrite(leds[i], HIGH);
  delay(500);
  for (int i = 0; i<=c-1;i++) digitalWrite(leds[i], LOW);
  delay(500);

  //delay(1000);
  /*while (bits != 0B11111111111111) {
   int j = random(c);
   if (GetBit(bits,j)) {
   bits = bitON(bits,j);
   turn(bits,t*12);
   }
   }
   
   for (int k = 
   int bits = 0;
   for (int i = 0; i<=c-1;i++) {
   bitON(bits,i);
   delay(t);
   }
   */
}

void turn(int data, int de) {
  for (int i=0;i<=c-1;i++)   {
    if (GetBit(data,i) == 1) 
      digitalWrite(leds[i],HIGH);
    else 
      digitalWrite(leds[i],LOW);
  }
  delay(de);
}





