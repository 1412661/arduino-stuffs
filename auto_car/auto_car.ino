#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5);

const byte Q1 = A0;  //Chân đọc giá trị quang trở bên phải
const byte Q2 = A1;   //Chân đọc giá trị quang trở bên trái
const byte Q3 = A5;  //Chân đọc giá trị biến trở điều khiển tốc độ
const byte Q4 = A4;   //Chân đọc mốc quang trở
const byte Q5 = A3;    //Chân đọc hệ số tăng tốc góc

const byte MOTOR1 = 9; //Chân điều khiển động cơ bên phải
const byte MOTOR2 = 10; //Chân điều khiển động cơ bên trái

byte c = 0;    //Biến đếm cho LCD

byte normal_power, boost_power;
int Q1_val, Q2_val, Q3_val, Q4_val, Q5_val;    //Giá trị biến trở/quang trở

// >  is black

void setup() {
  lcd.begin(16, 2);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(Q1, INPUT);
  pinMode(Q2, INPUT);
  pinMode(Q3, INPUT);
  pinMode(Q4, INPUT);

  Q3_val = round(analogRead(Q3)*0.249);
  Q4_val = analogRead(Q4);

  Q5_val = round(analogRead(Q5)/10.33);

  normal_power = Q3_val;
  boost_power = round(Q3_val*(Q5_val+100)/100);
  if (boost_power > 255) boost_power = 255;

  delay(1);
}

void loop() {
  Q1_val = analogRead(Q1);
  Q2_val = analogRead(Q2);

  if (c == 200) {
    lcd.clear();
    lcd.print("Q4:");
    lcd.print(Q4_val);
    lcd.setCursor(7,0);
    lcd.print("Q1:");
    lcd.print(Q1_val);
    lcd.setCursor(0,1);
    lcd.print("DC:");
    lcd.print(Q3_val);
    lcd.setCursor(7,1);
    lcd.print("Q2:");
    lcd.print(Q2_val);
    lcd.setCursor(14,0);
    lcd.print("BE");
    lcd.setCursor(14,1);
    lcd.print(Q5_val);
    c = 0; 
  } 
  else {
    c = c + 1; 
  }


  if (sensor_left())  turn_left(); 
  else if (sensor_right()) turn_right();
  else if (sensor_white()) gogogo();


  delay(1);
}

boolean sensor_left() {
  if ((Q1_val >= Q4_val) and (Q2_val < Q4_val)) 
    return(true); 
  else return(false);
}

boolean sensor_right() {
  if ((Q1_val < Q4_val) and (Q2_val >= Q4_val)) return(true); 
  else return(false);
}

boolean sensor_black() {
  if ((Q1_val >= Q4_val) and (Q2_val >= Q4_val)) return(true); 
  else return(false);
}

boolean sensor_white() {
  if ((Q1_val < Q4_val) and (Q2_val < Q4_val)) return(true); 
  else return(false);
}

//ACTION

void turn_left() {
  analogWrite(MOTOR2, boost_power);
  analogWrite(MOTOR1, 0);
}

void turn_right() {
  analogWrite(MOTOR1, boost_power);
  analogWrite(MOTOR2, 0);
}

void gogogo() {
  analogWrite(MOTOR1, normal_power);
  analogWrite(MOTOR2, normal_power);
}




