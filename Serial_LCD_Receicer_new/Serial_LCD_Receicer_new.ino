#include <SerialCommand.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Servo.h>
;pua
LiquidCrystal_I2C lcd(0x27,16,2);
SerialCommand SCmd;
Servo myservo;

int step;

int password[30];
int password_length = 0;

int PASSWORD[30];
int PASSWORD_LENGTH;

int new_password_length = 0;
int new_password[30];

int de_eeprom = 50;
int pos, i;

void setup() {  
  lcd.init();
  lcd.backlight();
  myservo.attach(3);
  Serial.begin(115200);
  welcome();    
  close_door();

  SCmd.addCommand("PUSH", PUSH);
  SCmd.addCommand("CLEAR", CLEAR);
  SCmd.addCommand("ENTER", ENTER);  
  
  SCmd.addCommand("OPEN", open_door_); 
  SCmd.addCommand("CLOSE", close_door_); 
  SCmd.addCommand("CHANGE", r_change_pass); 
  
  ReadPassword();
  //ShowPassword();
  //Serial.println("Ready !");
}

void loop() {
  SCmd.readSerial();
}

void ENTER() {
  if (step == 1) return;

  lcd.clear();

  switch (step) {
  case 21: 
    {
      if (!check()) 
      {
        lcd.print("WRONG PASS !");   
        delay(1500);
        welcome();
        break;
      }    
      else 
      {
        lcd.print("OK !"); // do some thing
        open_door();
        delay(10000);
        close_door();
        welcome();
        break;
      }

    }
  case 31: 
    {
      if (!check()) {
        lcd.print("WRONG PASS !");
        delay(1500);
        welcome();        
      }
      else 
      {
        mess("ENTER NEW PASS:");
        clear_memory_pass();
        step = 32;
      }
      break;
    }
  case 32: 
    {
      mess("RE ENTER PASS:");
      step = 33;
      break;
    }
  case 33: 
    {
      lcd.clear();
      if (!check_match()) {
        lcd.print("PASS NOT MATCH !");         
      } 
      else {
        lcd.print("PASS CHANGED !");
        update_pass();
      }
      delay(1500);
      welcome();
    }
  }
}

void close_door() {
  for (pos = 90; pos<=179; pos++) {
    myservo.write(pos);
    delay(10); 
  }
}

void open_door() {
  for (pos = 179; pos>=70; pos--) {
    myservo.write(pos);
    delay(10); 
  }
}

void mess(char c[16]) {
  lcd.print(c);
  lcd.setCursor(0,1);
  lcd.print("________________");
  lcd.setCursor(0,1);
}

void CLEAR() {
  if (step == 1) return;
  lcd.setCursor(0,1);
  lcd.print("________________");
  lcd.setCursor(0,1);  
  if (step == 33) clear_new_pass();
  else clear_memory_pass();
}

void PUSH() {
  byte arg = atoi(SCmd.next());
  if (step == 1) {
    if (arg == 1) login();
    if (arg == 2) change_pass(); 
  } 
  else {
    lcd.print(arg);
    if (step == 33) {
      new_password[new_password_length] = arg;
      new_password_length++;
    } 
    else {
      password[password_length] = arg;
      password_length++;
    } 
  }
}

void welcome() {
  clear_memory_pass();
  clear_new_pass();
  lcd.clear();
  lcd.print("1: LOGIN");
  lcd.setCursor(0,1);
  lcd.print("2: CHANGE PASS");
  step = 1;
  delay(10);
}

void login() {
  lcd.clear();
  mess("ENTER PASSWORD:");
  step = 21;
}

void change_pass() {
  lcd.clear();
  mess("ENTER OLD PASS:");
  step = 31;
}

void ReadPassword() {
  delay(de_eeprom);
  PASSWORD_LENGTH = EEPROM.read(0);
  delay(de_eeprom);
  for (i = 1; i <= PASSWORD_LENGTH; i++) {    
    PASSWORD[i-1] = EEPROM.read(i);   
    delay(de_eeprom);
  }
}

void clear_memory_pass() {
  for (i = 0; i <= 30; i++) password[i] = 0;
  password_length = 0; 
}

void clear_new_pass() {
  for (i = 0; i <= 30; i++) new_password[i] = 0;
  new_password_length = 0; 
}

boolean check_match() {
  if (password_length != new_password_length) return false;
  for (i = 0; i <= password_length-1; i++)
    if (password[i] != new_password[i]) return false;
  return true; 
}

boolean check() {
  if (password_length != PASSWORD_LENGTH) return false;
  for (i = 0; i <= password_length-1; i++)
    if (password[i] != PASSWORD[i]) return false;
  return true; 
}

void update_pass() {
  delay(de_eeprom);
  EEPROM.write(0,password_length);
  delay(de_eeprom);
  for (i = 1; i<=password_length; i++) {    
    EEPROM.write(i,password[i-1]); 
    delay(de_eeprom);
  }

  PASSWORD_LENGTH = password_length;
  for (i = 0; i <= password_length-1; i++) 
    PASSWORD[i] = password[i];
}

void ShowPassword() {
  delay(20);
  Serial.println(PASSWORD_LENGTH);
  for (i = 0; i <= PASSWORD_LENGTH-1; i++)
    Serial.print(PASSWORD[i]);
}

void r_change_pass() {
  char *arg;
  
  arg = SCmd.next();
  password_length = strlen(arg);
  for (int i = 0; i<= password_length-1;i++) password[i] = arg[i];
  
  update_pass();
}

void unrecognized()
{
}

void close_door_() {
  for (pos = 90; pos<=179; pos++) {
    myservo.write(pos);
    delay(10); 
  }
  delay(10000);
  welcome();
}

void open_door_() {
  for (pos = 179; pos>=70; pos--) {
    myservo.write(pos);
    delay(10); 
  }
  delay(10000);
  welcome();
}




