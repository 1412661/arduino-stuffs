byte up = 5;
byte down = 6;
byte left = 7;
byte right = 8;

byte D1 = 10;
byte D2 = 11;
byte G1 = 12;
byte G2 = 13;

void setup() {
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP); 

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT); 

  stand();
}

void loop() {
  if (digitalRead(up) == 0) 
    go_up();
  else
    if (digitalRead(down) == 0) go_down();
    else
      if (digitalRead(left) == 0) go_left();
      else 
        if (digitalRead(right) == 0) go_right();
      else stand();


  delay(10);
}

void out(byte pin, byte state) {
  digitalWrite(pin, state); 
}

void go_up() {
  out(D1, HIGH);
  out(D2, LOW);
  out(G1, HIGH);
  out(G2, LOW);
}

void go_down() {
  out(D2, HIGH);
  out(D1, LOW);
  out(G2, HIGH);
  out(G1, LOW);
}

void go_left() {
  out(D1, HIGH);
  out(D2, LOW);
  out(G2, HIGH);
  out(G1, LOW);
}

void go_right() {
  out(D2, HIGH);
  out(D1, LOW);
  out(G1, HIGH);
  out(G2, LOW);
}

void stand () {
  out(D2, LOW);
  out(D1, LOW);
  out(G1, LOW);
  out(G2, LOW);
}


