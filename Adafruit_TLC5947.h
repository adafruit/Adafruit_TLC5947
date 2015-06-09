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
  Adafruit_TLC5947(uint32_t n, uint32_t c, uint32_t d, uint32_t l, uint32_t b);
  boolean begin(void);
  void setPWM(uint32_t chan, uint32_t pwm);
  void setLED(uint32_t lednum, uint32_t r, uint32_t g, uint32_t b);
  void write(void);
  void print();
 private:
  uint32_t *pwmbuffer;
  uint32_t numdrivers, _clk, _dat, _lat, _blk;
};

#endif
