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
#ifndef _ADAFRUIT_TLC5947_H
#define _ADAFRUIT_TLC5947_H

#include <Arduino.h>

class Adafruit_TLC5947 {
 public:
  Adafruit_TLC5947(const uint8_t& n, const uint8_t& c, const uint8_t& d, const uint8_t& l, const uint8_t& b);
  ~Adafruit_TLC5947(void);
  boolean begin(void);
  void setPWM(const uint16_t& chan, const uint16_t& pwm);
  void setLED(const uint8_t& lednum, const uint16_t& b, const uint16_t& r, const uint16_t& g);
  void write(void);
 private:
  uint16_t *pwmbuffer;
  uint8_t num, _clk, _dat, _lat, _blk;
};

#endif
