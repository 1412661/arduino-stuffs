const int delta = 200;
int a,b;

byte sensor = A0;
byte led = 13;
byte ct = 8;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(ct, INPUT_PULLUP);
  digitalWrite(led, LOW);

  a = analogRead(sensor);

}

void loop() {
  b = analogRead(sensor);
  Serial.println(a);
  Serial.println(b);
  Serial.println();
  Serial.println();
  if (abs(a-b) > delta) {
    while (true) {
      digitalWrite(led, HIGH);
      if (digitalRead(ct) == LOW) break;
    }
  }
  else {
    digitalWrite(led, LOW);
    a = b; 
  }
  delay(5);
}


