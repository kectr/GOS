#include "lib/byteOperations/byteOperations.h"
#include "stdio.h"

int main(){
    uint8_t x = 0x01;
    toggleBit(&x,0);
    printf("%d",readBit(x,0));
    return 0;
}