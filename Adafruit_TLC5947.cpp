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

Adafruit_TLC5947::Adafruit_TLC5947(uint32_t n, uint32_t c, uint32_t d, uint32_t l, uint32_t b) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;
  _blk = b;
  pwmbuffer = (uint32_t *)calloc(24*n, sizeof(uint32_t));
}

void Adafruit_TLC5947::write(void) {
  digitalWrite(_blk, HIGH);
  digitalWrite(_lat, LOW);
  digitalWrite(_blk, LOW);
  for (int32_t c=24*numdrivers - 1; c >= 0 ; c--) {
    for (int32_t b=11; b>=0; b--) {
      digitalWrite(_clk, LOW);
      if (pwmbuffer[c] & (1 << b))   {
        digitalWrite(_dat, HIGH);
        //Serial.println(1);
      } else {
        digitalWrite(_dat, LOW);
        //Serial.println(0);
       }
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_lat, HIGH);  
  digitalWrite(_lat, LOW);
}

void Adafruit_TLC5947::setPWM(uint32_t chan, uint32_t pwm) {
  if (pwm > 4095) pwm = 4095;
  if (chan > 24*numdrivers) return;
  pwmbuffer[chan] = pwm;  
}

void Adafruit_TLC5947::setLED(uint32_t lednum, uint32_t b, uint32_t r, uint32_t g) {
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

void Adafruit_TLC5947::print() {
	for(int i = 0;i < 192;++i) {
		Serial.println(pwmbuffer[i]);
		Serial.println(' ');
	}
	Serial.println("END");
}
