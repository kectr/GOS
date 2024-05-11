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
    // wd.drawLine(0, 0, 15, 6);
    wd.drawShape(3, 3,data);
    wd.content.printout(0);

    return 0;
}