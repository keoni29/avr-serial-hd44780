#pragma once

/**
 * Ringbuffer
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    volatile uint8_t *buffer;
    uint16_t length;
    volatile uint16_t end;
    volatile uint16_t start;
}RingBuffer;

void ringBufferCreate(RingBuffer *rb, uint16_t length);
uint8_t ringBufferRead(RingBuffer *rb);
void ringBufferWrite(RingBuffer *rb, const uint8_t c);
bool ringBufferAvailable(RingBuffer *rb);