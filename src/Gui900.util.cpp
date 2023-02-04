#include "Gui900.util.h"

uint16_t Gui900::Util::color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

int Gui900::Util::centerAlign(int containerSize, int objectSize)
{
    return (containerSize / 2) - (objectSize / 2);
}

int Gui900::Util::centerAlignEnd(int containerSize, int objectSize)
{
    return (containerSize / 2) + (objectSize / 2);
}