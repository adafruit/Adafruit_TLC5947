/*!
 *  @file Adafruit_TLC5947.cpp
 *
 *  @mainpage Adafruit 24-channel PWM/LED driver
 *
 *  @section intro_sec Introduction
 *
 * 	Driver for Microchip's TLC5947
 *
 * 	This is a library for the Adafruit TLC5947
 * 	http://www.adafruit.com/products/
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section author Author
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include <Adafruit_TLC5947.h>

/*!
 *    @brief  Instantiates a new TLC5947 class
 *    @param  n
 *            num of drivers (boards)
 *    @param  c
 *            Arduino pin connected to TLC5947 clock pin
 *    @param  d
 *            Arduino pin connected to TLC5947 data pin
 *    @param  l
 *            Arduino pin connected to TLC5947 latch pin
 */
Adafruit_TLC5947::Adafruit_TLC5947(uint16_t n, uint8_t c, uint8_t d,
                                   uint8_t l) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;

  pwmbuffer = (uint16_t *)malloc(2 * 24 * n);
  memset(pwmbuffer, 0, 2 * 24 * n);
}

/*!
 *    @brief  Releases allocated resources
 */

Adafruit_TLC5947::~Adafruit_TLC5947() { free(pwmbuffer); }

/*!
 *    @brief  Writes PWM data to the all connected TLC5947 boards
 */
void Adafruit_TLC5947::write() {
  digitalWrite(_lat, LOW);
  // 24 channels per TLC5974
  for (int16_t c = 24 * numdrivers - 1; c >= 0; c--) {
    // 12 bits per channel, send MSB first
    for (int8_t b = 11; b >= 0; b--) {
      digitalWrite(_clk, LOW);

      if (pwmbuffer[c] & (1 << b))
        digitalWrite(_dat, HIGH);
      else
        digitalWrite(_dat, LOW);

      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);

  digitalWrite(_lat, HIGH);
  digitalWrite(_lat, LOW);
}

/*!
 *    @brief  Set the PWM channel / value
 *    @param  chan
 *            channel number ([0 - 23] on each board, so channel 2 for second
 * board will be 25)
 *    @param  pwm
 *            pwm value [0-4095]
 */
void Adafruit_TLC5947::setPWM(uint16_t chan, uint16_t pwm) {
  if (pwm > 4095)
    pwm = 4095;
  if (chan >= 24 * numdrivers)
    return;
  pwmbuffer[chan] = pwm;
}

/*!
 *    @brief  Get the PWM value for channel.
 *    @param  chan
 *            channel number ([0 - 23] on each board, so channel 2 for second
 * board will be 25)
 *    @return PWM value ([0 - 4095]) for valid channels, 0 for non-existing
 * channels.
 */
uint16_t Adafruit_TLC5947::getPWM(uint16_t chan) {
  if (chan >= 24 * numdrivers) {
    return 0;
  } else {
    return pwmbuffer[chan];
  }
}

/*!
 *    @brief  Set LED
 *    @param  lednum
 *            led number
 *    @param  r
 *            red value [0-255]
 *    @param  g
 *            green value [0-255]
 *    @param  b
 *            blue value [0-255]
 */
void Adafruit_TLC5947::setLED(uint16_t lednum, uint16_t r, uint16_t g,
                              uint16_t b) {
  setPWM(lednum * 3, r);
  setPWM(lednum * 3 + 1, g);
  setPWM(lednum * 3 + 2, b);
}

/*!
 *    @brief  Setups the HW
 *    @return True if initialization was successful, otherwise false.
 */
boolean Adafruit_TLC5947::begin() {
  if (!pwmbuffer)
    return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  return true;
}
