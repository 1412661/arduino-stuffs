/* Note: 
 This code is written for Attiny13A-PU for shiftout to SN74HC595N
 Collect from Internet by quocbao747
 */

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

//Kiểm tra bit thứ i là 0 hay 1
#define isOn(S, i) (S & (1 << j))

//Set bit tại vị trí thứ i là 1
#define bitOn(i, S) (S | (1 << i))

//Set bit tại vị trí thứ i là 0
#define bitOFF(S, i) (S &= ~(1 << i))

//Đảo bit tại vị trí thứ i
#define bitToggle(S, i) (S ^= (1 << i))

//Kiểm tra số x có phải là lũy thừa của 2 không
#define isPowerOfTwo(x) ((x & (x - 1)) == 0)

//set tất cả n bit ngoài cùng bên phải của S = 1
#define setAll(S, n) (S = (1 << n) - 1)

//Trả về x % N, với N là lũy thừa của 2
#define module2(x, N) ((x) & (N - 1))

//Tìm giá trị lũy thừa của 2 gần nhất với x
#define nearestPowerOfTwo(x) ((int)pow(2.0, (int)((log((double)x) / log(2.0)) + 0.5))) 

/* Configuration */
//Pin connected to ST_CP (pin 12) of 74HC595
byte latchPin = 1;
//Pin connected to SH_CP (pin 11) of 74HC595
byte clockPin = 2;
////Pin connected to DS (pin 14) of 74HC595
byte dataPin = 0;

byte numbers[] = {
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

void setup() {
  DDRB = 0B111111;
  TCCR0B |=  _BV(CS02) | _BV(CS00) ; 
}

void loop(){
  for (int i = 0; i < 10; i++) {
    led7(i);
    delay(1000);
  }
  turn(0B11111111);
  delay(1000);
}

void led7(int number) {
  switch(number) {
  case 0:
    turn(0B00000011);
    break;
  case 1:
    turn(0B10011111);
    break;
  case 2:
    turn(0B00100101);
    break;
  case 3:
    turn(0B00001101);
    break;
  case 4:
    turn(0B10011001);
    break;
  case 5:
    turn(0B01001001);
    break;
  case 6:
    turn(0B01000001);
    break;
  case 7:
    turn(0B00011111);
    break;
  case 8:
    turn(0B00000001);
    break;
  case 9:
    turn(0B00001001);
    break;
  }
}

void turnofftim() {
  cbi(TCCR0A, COM0A1);
  cbi(TCCR0A, COM0B1);
}

void turnontim() {
  sbi(TCCR0A, COM0A1);
  sbi(TCCR0A, COM0B1);
}

void shiftout(uint8_t val) {
  turnofftim();
  uint8_t i;

  for (i = 0; i < 8; i++)  {
    if (!!(val & (1 << (i))))
      PORTB = sbi(PORTB,dataPin);
    else
      PORTB = cbi(PORTB,dataPin);
    PORTB = sbi(PORTB, clockPin);
    PORTB = cbi(PORTB, clockPin);			
  }
  turnontim();
}

void turn(byte bits) {
  PORTB &= (1<<latchPin);
  shiftout(bits);
  PORTB |= (1<< latchPin); 
}

void digitalwrite(uint8_t pin, uint8_t val) {
  if (val)
    PORTB = sbi(PORTB, pin);
  else
    PORTB = cbi(PORTB, pin);
}




