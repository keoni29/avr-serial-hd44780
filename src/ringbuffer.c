/**
 * Ringbuffer
*/

#include "ringbuffer.h"

void ringBufferCreate(RingBuffer *rb, uint16_t length) {
    rb->buffer = (uint8_t *)malloc(sizeof(*(rb->buffer)) * length);
    rb->length = length;
    rb->end = 0;
    rb->start = 0;
}

/** Read from ringbuffer
 * @return value from ringbuffer
*/
uint8_t ringBufferRead(RingBuffer *rb) {
    uint8_t c = *(rb->buffer + rb->start);
    
    if (rb->start != rb->end) {
        rb->start ++;
        if (rb->start >= rb->length) {
            rb->start = 0;
        }
    }

    return c;
}

/** Write to ringbuffer. Will overwrite buffer if buffer length is exceeded.
 * TODO: Fix ringbuffer overwrite
*/
void ringBufferWrite(RingBuffer *rb, const uint8_t c) {
    *(rb->buffer + rb->end) = c;

    rb->end ++;

    if (rb->end >= rb->length) {
        rb->end = 0;
    }
}


/** Check if data is available in the buffer.
 * @return true if data is available in the buffer, otherwise return false
 */
bool ringBufferAvailable(RingBuffer *rb) {
    return (rb->start != rb->end);
}
