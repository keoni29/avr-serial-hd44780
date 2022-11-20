#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

#define DELAY_CLK 5
#define DELAY_LONG 800

#define RS (1<<2)
#define ENA (1<<3)
#define D4 (1<<4)
#define D5 (1<<5)
#define D6 (1<<6)
#define D7 (1<<7)

#define HIGH 1
#define LOW 0

void pulseClock(void ) {
  _delay_us(DELAY_CLK);
  PORTD |= ENA; // Enable pin HIGH
  _delay_us(DELAY_CLK);
  PORTD &= ~ENA; // Enable pin LOW
  _delay_us(DELAY_CLK);
}


static void lcdWrite4(uint8_t value) {
  PORTD &= ~RS; // RS pin LOW
  _delay_us(DELAY_LONG);

  PORTD &= ~(D4 | D5 | D6 | D7);

  PORTD |= ((value >> 0) & 1) ? (D4) :  0;
  PORTD |= ((value >> 1) & 1) ? (D5) :  0;
  PORTD |= ((value >> 2) & 1) ? (D6) :  0;
  PORTD |= ((value >> 3) & 1) ? (D7) :  0;
  
  pulseClock();
}

/**
 * @brief
 * @param command
 * @param reg register select pin value HIGH or LOW
 */
static void lcdWrite(uint8_t command, uint8_t reg) {
  PORTD = reg ? PORTD | RS : PORTD &~RS; // Set or clear RS pin based on reg value
  _delay_us(DELAY_LONG);

  PORTD = (PORTD & ~(D4 | D5 | D6 | D7));
  PORTD |= ((command >> 4) & 1) ? (D4) :  0;
  PORTD |= ((command >> 5) & 1) ? (D5) :  0;
  PORTD |= ((command >> 6) & 1) ? (D6) :  0;
  PORTD |= ((command >> 7) & 1) ? (D7) :  0;

  pulseClock();

  PORTD = (PORTD & ~(D4 | D5 | D6 | D7));
  PORTD |= ((command >> 0) & 1) ? (D4) :  0;
  PORTD |= ((command >> 1) & 1) ? (D5) :  0;
  PORTD |= ((command >> 2) & 1) ? (D6) :  0;
  PORTD |= ((command >> 3) & 1) ? (D7) :  0;

  pulseClock();
}

void lcdBegin(uint8_t cols, uint8_t rows) {
  DDRD |= RS | ENA | D4 | D5 | D6 | D7;

  lcdWrite4(0b0011);
  lcdWrite4(0b0011);
  lcdWrite4(0b0011);
  lcdWrite4(0b0010);
  
  
  // send the "function set" command to configure display dimensions
  lcdWrite(0b00101100, LOW);

  // send the "display on/off control" command (1000) to power on the
  // display (0100), enable cursor (0010), and enable cursor blink (0001)
  lcdWrite(0b00001111, LOW);
  
  // clear the display
  lcdWrite(0b00000001, LOW);
  
  // send the "entry mode set" command to set left-to-right printing (110)
  lcdWrite(0b00000110, LOW);

  
}

void lcdPrint(const char c) {
  lcdWrite(c, HIGH);
}

void lcdPrintln(const char* str) {
  char c;
  while ((c = *str)) {
    lcdWrite(c, HIGH);
    str ++;
  }
}
