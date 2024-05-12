#include "lib/BitArray2d/BitArray2d.h"
#include "lib/Window/window.h"
#include "fonts/font8x8_ib8x8uLSB0-127.h"

int main()
{
    char del[] = {char(127),'\0'};
    string dels = del;
    textWindow txt(font8x8_ib8x8u,8,8);
    txt.initialize(32,16,0,0,0);
    txt.strToFont("ab\ne");
    txt.content.printouttexture(1);
    txt.strToFont(del);
    txt.content.printouttexture(1);
    return 0;
}