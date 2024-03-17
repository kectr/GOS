#include <cstdint>
uint8_t readBit(uint8_t value, uint8_t position);
void writeBit(uint8_t *byteAdr, uint8_t position, uint8_t value);
void setBit(uint8_t *byteAdr, uint8_t position);
void clearBit(uint8_t *byteAdr, uint8_t position);
void toggleBit(uint8_t *byteAdr, uint8_t position);