#include "byteOperations.h"

void setBit(uint8_t *byteAdr, uint8_t position)
{
    *byteAdr |= 0x01 << position;
}

void clearBit(uint8_t *byteAdr, uint8_t position)
{
    *byteAdr &= ~(0x01 << position);
}

void toggleBit(uint8_t *byteAdr, uint8_t position)
{
    *byteAdr ^= 0x01 << position;
}

uint8_t readBit(uint8_t value, uint8_t position)
{
    return (value >> position) & 1;
}

void writeBit(uint8_t *byteAdr, uint8_t position, uint8_t value)
{
    (value ? setBit(byteAdr, position) : clearBit(byteAdr, position));
}
