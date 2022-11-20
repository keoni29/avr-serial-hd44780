/**
 * filename : uart.c
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
 */

#include <avr/io.h>
#include "uart.h"

/* Highest possible baudrate @ 16MHz */
#define BAUDRATE 9600UL

#define UB ((F_CPU / (BAUDRATE * 16UL)) - 1)

/**
 * Initialize the UART.
 */
inline void uart_init(void)
{
    UBRRH = (UB >> 8) & 0xFF;
	UBRRL = (UB & 0xFF);

	UCSRB = (1<<RXEN)|(1<<TXEN);
}


/**
 * Read a character from the UART.
 * Waits until a character is received.
 * @return The received character
 */
inline uint8_t uart_read(void)
{
    while(!(UCSRA & (1 << RXC)));
    return UDR;
}


/** 
 * Write a string to the UART.
 * Waits for the whole string to be sent.
 */
void uart_write_string(const char *string)
{
	/* Wait until sender is ready. Then send a character. */
	while(*string)
	{
		while (!(UCSRA & (1 << UDRE)));
		UDR = *string;
		++string;
	}
}
