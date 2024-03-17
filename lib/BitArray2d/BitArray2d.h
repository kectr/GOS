// I used bit arrays for storing ones and zeros while saving memory for arduino
// data[y*width_8+x/8]##this is very important structure for finding byte from cordinates

#include <stdint.h>
#include <stdlib.h>
#include "../byteOperations/byteOperations.h"

class BitArray2d
{
private:
    /* data */
public:
    uint16_t heigt;
    uint16_t width;
    uint16_t width_8; //(width+7)/8
    uint8_t *data;

    BitArray2d(uint16_t heigt, uint16_t width, uint8_t *data);
    BitArray2d(uint16_t heigt, uint16_t width);
    void initialize(uint16_t heigt, uint16_t width);
    ~BitArray2d();
    
    uint8_t read(uint16_t x, uint16_t y);
    void write(uint16_t x, uint16_t y, uint8_t value);
};
