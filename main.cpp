#include "lib/BitArray2d/BitArray2d.h"
#include "lib/Window/window.h"

int main()
{
    drawableWindow wd;
    wd.initialize(32, 16, 0, 0, 0);

    uint8_t data[] = {0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa};

    BitArray2d arr(4, 4, data);
    wd.drawShape(0, 0, arr);
    wd.content.printout();

    return 0;
}