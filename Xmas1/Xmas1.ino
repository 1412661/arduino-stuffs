//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 
//Pin connected to ST_CP of 74HC595
const byte latchPin = 0;
//Pin connected to SH_CP of 74HC595
const byte clockPin2 = 1;
////Pin connected to DS of 74HC595
const byte dataPin2 = 2;
const byte clockPin1 = 3;
////Pin connected to DS of 74HC595
const byte dataPin1 = 4;
const byte timer =  2;

  byte i, sreg;
void setup() {
  //set pins to output so you can control the shift register
  DDRB = B111111;
  TCCR0B |=  _BV(CS02) | _BV(CS00) ; 
}

void turn(byte bits1, byte bits2) {
    //digitalWrite(latchPin, LOW);
    PORTB &= (1<<latchPin);
    // shift out the bits:
    //shiftOut(dataPin, clockPin, LSBFIRST, bits); 
    shiftout1(bits1);shiftout2(bits2);
    
    //take the latch pin high so the LEDs will light up:
    //digitalWrite(latchPin, HIGH);
    PORTB |= (1<< latchPin); 
    // pause before next value:
}

void _de(byte c = 1) {
  for (byte i=0;i<c;i++)
  delayMicroseconds(timer*5000);
}

void loop(){
  //1
  byte k,i,bi1,bi2,j;
  bi1=B10001000;
  bi2=B10000000;
  j=B10000000;
  k=B10000000;
  for (i = 1; i<= 100;i++) {
    turn(bi2,bi1);
    _de(2);
    bi1 = bi1 >> 1;
    bi2 = bi2 >> 1;
    if (bi2 == 0) {
        j = j >> 1;
        k = k | j;
        bi2 = k;
    }
    if (bi1 == B00001000) bi1 = B10001000;
  }
  bi1=B10001000;
  bi2 = B11000000;
  for (i = 1; i<= 100;i++) {
    turn(bi2,bi1);
    _de(2);
    turn(bi2,bi1);
    _de(2);
    turn(bi2,bi1);
    _de(2);
    bi1 = bi1 >> 1;
    bi2 = bi2 >> 1;
    if (bi2 == 0) {
        j = j >> 1;
        k = k | j;
        bi2 = k;
    }
    if (bi1 == B00001000) bi1 = B10001000;
  }
}


void shiftout1(uint8_t val)
{
   turnofftim();
	uint8_t i;

	for (i = 0; i < 8; i++)  {
                //LSBFIRST
                if (!!(val & (1 << (i))))
                  PORTB = sbi(PORTB,dataPin1);
                else
                  PORTB = cbi(PORTB,dataPin1);
                PORTB = sbi(PORTB, clockPin1);
                PORTB = cbi(PORTB, clockPin1);			
	}
  turnontim();
}
void shiftout2(uint8_t val)
{
   turnofftim();
	uint8_t i;

	for (i = 0; i < 8; i++)  {
                //LSBFIRST
                if (!!(val & (1 << (i))))
                  PORTB = sbi(PORTB,dataPin2);
                else
                  PORTB = cbi(PORTB,dataPin2);
                PORTB = sbi(PORTB, clockPin2);
                PORTB = cbi(PORTB, clockPin2);			
	}
  turnontim();
}


void digitalwrite(uint8_t pin, uint8_t val)
{
 
//	uint8_t oldSREG = SREG;
//	cli();
	if (val) {
	  PORTB = sbi(PORTB, pin);
	} else {
	  PORTB = cbi(PORTB, pin);
	}
//	SREG = oldSREG;
//sei();
}

void turnofftim()
{
  cbi(TCCR0A, COM0A1);
  cbi(TCCR0A, COM0B1);
 // cbi(TCCR0A, COM0A0);
 // cbi(TCCR0A, COM0B0);
}
void turnontim()
{
   sbi(TCCR0A, COM0A1);
  sbi(TCCR0A, COM0B1);
  //sbi(TCCR0A, COM0A0);
  //sbi(TCCR0A, COM0B0);
}

