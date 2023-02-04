#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "Gui900.h"
#include "Gui900.display.mcufriend_kbv.h"

Gui900::Display_MCUFRIEND_kbv::Display_MCUFRIEND_kbv(int id) : display(), id(id)
{
}

void Gui900::Display_MCUFRIEND_kbv::init(Gui900::Orientation orientation)
{
    display.begin(id == 0 ? display.readID() : id);
    display.setRotation(orientation);
}

Adafruit_GFX &Gui900::Display_MCUFRIEND_kbv::gfx()
{
    return display;
}