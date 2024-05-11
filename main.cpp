#include "lib/BitArray2d/BitArray2d.h"
#include "lib/Window/window.h"

int main()
{
    uint8_t datas[] =
        {
            0x1f, 0x11, 0x11, 0x11, 0x1f, 0x00, 0x00, 0x00};
    BitArray2d data(8, 8, datas);
    drawableWindow wd;
    wd.initialize(32, 16, 0, 0, 0);
    wd.drawShape(31, 15,data);
    wd.content.printout(1);
    return 0;
}