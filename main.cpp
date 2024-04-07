#include "lib/BitArray2d/BitArray2d.h"
#include "lib/Window/window.h"

int main()
{
    drawableWindow wd;
    wd.initialize(32, 16, 0, 0, 0);

    uint8_t data[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

    BitArray2d arr(8, 8, data);

    // wd.content.printout();
    // wd.drawRectangle(0,0,31,15,1);
    // wd.content.printout();
    // wd.drawLine(0,0,31,15,1);
    // wd.content.printout();
    printf("ssafas");
    printf("\n%d\n", wd.drawShape(8, 8, arr));
    printf("ssafas");

    return 0;
}