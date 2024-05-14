#ifndef flabs
float flabs(float val)
{
    if (val < 0)
    {
        return -val;
    }
    else
    {
        return val;
    }
}
#endif