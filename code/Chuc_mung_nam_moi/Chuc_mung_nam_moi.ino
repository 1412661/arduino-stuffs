byte ledCount = 14;
byte ledPins[] = {
  A0,A1,A2,A3,7,8,A5,A4,6,5,9,10,11,12
};
byte wordCount = 4;
byte wordHead[] = {
  0,4,8,11,14
};
int timer = 200;
void setup () 
{
  byte i;
  for (i=0;i<ledCount;i++) {
    pinMode(ledPins[i],OUTPUT);
  }
}
boolean getBit(byte pin, int bits) 
{
  return (bits >> pin) & 1;
}
void turn(int bits) 
{
  for (byte i=0;i<ledCount;i++)
  {
    if (getBit(i,bits) == 1) 
    {
      digitalWrite(ledPins[i],HIGH);
    } 
    else {
      digitalWrite(ledPins[i],LOW);
    }
  }
  delay(timer);
}
void blinkled ()
{
  turn(0B10101010101010);
  delay(150);
  turn(0B1010101010101);
  delay(100);
  turn(0B10101010101010);
  delay(100);
  turn(0B1010101010101);
  delay(150);
}
void loop () 
{
  byte i;
  int bits = 0; 
  for (i=0;i<ledCount;i++) 
  {
    bits = bits | (1 << i);
    turn(bits);
  }
  delay(timer+200);
  for (i=0;i<ledCount;i++) 
  {
    bits = bits ^ (1 << i);
    turn(bits);
  }
  delay(timer+200);
  for (i=0;i<wordCount;i++) 
  {
    for (byte j=wordHead[i]+1;j<=wordHead[i+1];j++) 
    {
      bits = bits | (1 << (j-1));
    }
    turn(bits);
  } 
  delay(5000);
  for (i=0;i<wordCount;i++) 
  {
    for (byte j=wordHead[i]+1;j<=wordHead[i+1];j++) 
    {
      bits = bits ^ (1 << (j-1));
    }
    turn(bits);
  }
  delay(timer+200);
  for (i=0;i<wordCount;i++) 
  {
    for (byte j=wordHead[i]+1;j<=wordHead[i+1];j++) 
    {
      bits = bits | (1 << (j-1));
    }  
    turn(bits);
  } 
  delay(5000);
  for (i=0;i<wordCount;i++) 
  {
    for (byte j=wordHead[i]+1;j<=wordHead[i+1];j++) 
    {
      bits = bits >> 1;
    }
    turn(bits);
  }
  delay(timer+200);
  for (i=0;i<ledCount;i++) 
  {
    if (i % 2 == 0) {
      bits = bits | (1 << i);
      turn(bits);
    }
  }
  delay(timer+200);
  for (i=0;i<ledCount;i++) 
  {
    if (i % 2 == 1) {
      bits = bits | (1 << i);
      turn(bits);
    }
  }
  delay(5000);
  delay(timer+200);
  for (i=0;i<ledCount;i++) 
  {
    if (i % 2 == 0) {
      bits = bits | (1 << i);
      turn(bits);
    }
  }
  delay(timer+200);
  for (i=0;i<ledCount;i++) 
  {
    if (i % 2 == 1) {
      bits = bits | (1 << i);
      turn(bits);
    }
  }
  for (i=0;i<5;i++) 
  {  
    blinkled();
  }
}

