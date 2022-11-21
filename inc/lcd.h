#pragma once

#include <stdint.h>

/**
 * 
 * HD44780 Character Display Driver
 * 
 */

void lcdPrintln(const char*str);
void lcdPrint(const char c);
void lcdBegin(void);