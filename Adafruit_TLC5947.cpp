/*************************************************** 
  This is a library for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_TLC5947.h>

Adafruit_TLC5947::Adafruit_TLC5947(uint8_t n, uint8_t c, uint8_t d, uint8_t l, uint8_t b) {
  num = n;
  _clk = c;
  _dat = d;
  _lat = l;
  _blk = b;
  pwmbuffer = (uint16_t *)calloc(24*n, sizeof(uint16_t));
}

void Adafruit_TLC5947::write(void) {
  digitalWrite(_blk, HIGH);
  digitalWrite(_lat, LOW);
  digitalWrite(_blk, LOW);
  for (int16_t c=24*num - 1; c >= 0 ; c--) {
    for (int8_t b=11; b>=0; b--) {
      digitalWrite(_clk, LOW);
      if (pwmbuffer[c] & (1 << b))   {
        digitalWrite(_dat, HIGH);
      } else {
        digitalWrite(_dat, LOW);
       }
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_lat, HIGH);  
  digitalWrite(_lat, LOW);
}

void Adafruit_TLC5947::setPWM(uint16_t chan, uint16_t pwm) {
  if (pwm > 4095) pwm = 4095;
  if (chan > 24*num) return;
  pwmbuffer[chan] = pwm;  
}

void Adafruit_TLC5947::setLED(uint16_t lednum, uint16_t b, uint16_t r, uint16_t g) {
  setPWM(lednum*3, b);
  setPWM(lednum*3+1, r);
  setPWM(lednum*3+2, g);
}

boolean Adafruit_TLC5947::begin() {
  if (!pwmbuffer) return false;
  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  pinMode(_blk, OUTPUT);
  return true;
}
