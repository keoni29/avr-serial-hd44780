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
#include <avr/interrupt.h>
#include "uart.h"
#include "ringbuffer.h"

#define RX_BUFFER_LENGTH 64
//#define TX_BUFFER_LENGTH 64


typedef struct {
	RingBuffer rxBuffer;
	//RingBuffer txBuffer;
}Uart;

Uart mUart;

/* Highest possible baudrate @ 16MHz */
#define BAUDRATE 9600UL

#define UB ((F_CPU / (BAUDRATE * 16UL)) - 1)

/**
 * Initialize the UART.
 */
inline void uart_init(void)
{
	ringBufferCreate(&mUart.rxBuffer, RX_BUFFER_LENGTH);
	//ringBufferCreate(&mUart.txBuffer, TX_BUFFER_LENGTH);

    UBRRH = (UB >> 8) & 0xFF;
	UBRRL = (UB & 0xFF);

	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	sei();
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

/**
 * @return a positive integer when uart data is available
 * 
 */
inline bool uart_available(void) {
	return ringBufferAvailable(&mUart.rxBuffer);
}


/**
 * @return a character from the uart buffer if data is available, otherwise return 0.
 */
inline uint8_t uart_read(void) {
	return ringBufferRead(&mUart.rxBuffer);
}


ISR(USART_RXC_vect) {
	char c = UDR;

	ringBufferWrite(&mUart.rxBuffer, c);
}

