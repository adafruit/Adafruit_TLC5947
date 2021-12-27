/*!
 *  @file Adafruit_TLC5947.h
 *
 * 	Adafruit 24-channel PWM/LED driver
 *
 * 	This is a library for the Adafruit 24-channel PWM/LED driver:
 * 	http://www.adafruit.com/products/1429
 *
 *  These drivers uses SPI to communicate, 3 pins are required to
 *  interface: Data, Clock and Latch. The boards are chainable
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_TLC5947_H
#define _ADAFRUIT_TLC5947_H

#include <Arduino.h>

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            TLC5947 24-channel PWM/LED driver
 */
class Adafruit_TLC5947 {
public:
  Adafruit_TLC5947(uint16_t n, uint8_t c, uint8_t d, uint8_t l);
  ~Adafruit_TLC5947();

  boolean begin(void);

  void setPWM(uint16_t chan, uint16_t pwm);
  uint16_t getPWM(uint16_t chan);
  void setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b);
  void write();

private:
  uint16_t *pwmbuffer;

  uint16_t numdrivers;
  uint8_t _clk, _dat, _lat;
};

#endif
