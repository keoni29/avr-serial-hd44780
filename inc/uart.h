/**
 * filename : uart.h
 * 
 * Project: USB LED HID Board
 * Author: Koen van Vliet <8by8mail@gmail.com>
 * 
 * MIT License
 *
 * Copyright (c) 2019 Koen van Vliet
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * Usage:
 *      1. Initialize UART
 *      2. Read character from UART
 *      3. Write string to UART
 */

#ifndef _UART_H
#define _UART_H

#include <stdint.h>
#include <stdbool.h>

void uart_init(void);
uint8_t uart_read(void);
void uart_write_string(const char *string);
/**
 * @return a positive integer when uart data is available
 * 
 */
bool uart_available(void);


/**
 * @return a character from the uart buffer if data is available, otherwise return 0.
 */
uint8_t uart_read(void);

#endif // _UART_H