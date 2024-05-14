#ifndef sgn
#include <cstdint>
int8_t sgn(float val)
{
    if (0 == val)
    {
        return 0;
    }
    else
    {
        return (val > 0 ? 1 : -1);
    }
}
#endif
