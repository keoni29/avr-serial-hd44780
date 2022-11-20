#pragma once

#include <stdint.h>

/**
 * 
 * HD44780 Character Display Driver
 * 
 */

void lcdPrintln(const char*str);
void lcdPrint(const char c);
void lcdBegin(uint8_t cols, uint8_t rows);