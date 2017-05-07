int bientro = A0;
int dieukhien = 3;

int tocdo = 0;
int giatribientro = 0;

void setup()
{
  pinMode(dieukhien, OUTPUT);
  pinMode(bientro, INPUT);  
}

void loop()
{
  giatribientro = analogRead(bientro);
  tocdo = map(giatribientro, 0, 1023, 0, 255);
  analogWrite(dieukhien, tocdo);
}

