int button = 7;
int speaker = 8;
int led = 6;

void setup() {
  Serial.begin(9600); 
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  int reading = digitalRead(button);
  if (reading == LOW) {
    xi_nhan();
  } 
  else {
    noTone(speaker);
  }
}

void xi_nhan() {
  tone(speaker, 1000);
  digitalWrite(led, HIGH);
  delay(300);
  noTone(speaker);
  digitalWrite(led, LOW);
  delay(300);
}




