#include "BitArray2d.h"

BitArray2d::BitArray2d()
{
}

void BitArray2d::takeDataFromMem(){
    BitArray2d::data = new uint8_t[heigt * width_8];
}

void BitArray2d::initialize(uint16_t width, uint16_t heigt)
{
    BitArray2d::heigt = heigt;
    BitArray2d::width = width;
    BitArray2d::width_8 = (width + 7) / 8;
}

BitArray2d::BitArray2d(uint16_t width, uint16_t heigt, uint8_t *data)
{
    BitArray2d::initialize(heigt, width);
    BitArray2d::data = data;
}

BitArray2d::BitArray2d(uint16_t width, uint16_t heigt)
{
    BitArray2d::initialize(width, heigt);
    BitArray2d::takeDataFromMem();
}

BitArray2d::~BitArray2d()
{
    if (data != nullptr)
    {
        delete[] data;
    }
}

uint8_t BitArray2d::read(uint16_t x, uint16_t y)
{
    return readBit(data[y * width_8 + x / 8], 7 - (x % 8));
}

void BitArray2d::write(uint16_t x, uint16_t y, uint8_t value)
{
    writeBit(data + y * width_8 + x / 8, 7 - (x % 8), value);
}
