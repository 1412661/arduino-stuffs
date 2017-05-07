/****************************************/
/* PROJECT: Dung arduino dieu khien motor dieu chinh toc do bang bien tro */
/* Author: Ngo Huynh Ngoc Phu (machtudong@gmail.com) */
/****************************************/

int bientro = A0;
int dieukhien = 3;

int tocdo = 1;
int giatribientro = 0;

void setup(){
  pinMode(dieukhien, OUTPUT);
  pinMode(bientro, INPUT);
  pinMode(10, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop(){
  if (digitalRead(10) == 0) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  } 
  else {
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }
  giatribientro = analogRead(bientro);
  tocdo = map(giatribientro, 0, 1023, 0, 255);
  analogWrite(dieukhien, tocdo);
  delay(200);
}




