#define F_CPU 9000000L
#define STK500 false //if STK500 = true, nothing happen

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


void delay_(uint16_t milliseconds) {
  for(; milliseconds>0; milliseconds--) _delay_ms(1);
}

void analogWrite_(byte pin, byte power){
  DDRB |= (1<<pin);
  
#if STK500
  TCCR0A = (1<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(1<<COM0A0);          // invertierte 8-Bit Fast PWM an OC0A
#else
  TCCR0A = (1<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(0<<COM0A0);          // nicht invertierte Fast PWM an OC0A
#endif
  TCCR0B = (1<<CS00);             // precaler

  OCR0A = power;
}


void setup() {
}

void loop() {
  analogWrite_(PB0, 50);
}

