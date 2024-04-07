// I used bit arrays for storing ones and zeros while saving memory for arduino
// data[y*width_8+x/8]##this is very important structure for finding byte from cordinates
#ifndef BitArray2d_h
#define BitArray2d_h

#ifndef byteOperations_h
#include "../byteOperations/byteOperations.h"
#endif


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


class BitArray2d
{
private:
    /* data */
public:
    uint16_t height;
    uint16_t width;
    uint16_t width_8; //(width+7)/8
    uint8_t *data = nullptr;

    BitArray2d();
    BitArray2d(uint16_t width, uint16_t height, uint8_t *data);
    BitArray2d(uint16_t width, uint16_t height);
    void initialize(uint16_t width, uint16_t height);
    void takeDataFromMem();
    void printout(uint8_t spaces = 0);
    void fill(uint8_t value = 0);
    ~BitArray2d();

    uint8_t read(uint16_t x, uint16_t y);
    void write(uint16_t x, uint16_t y, uint8_t value);
};
#endif