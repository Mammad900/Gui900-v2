#ifndef __GUI900_DISPLAY_MCUFRIEND_KBV_H__
#define __GUI900_DISPLAY_MCUFRIEND_KBV_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "Gui900.h"

namespace Gui900
{
    /// @brief Uses the MCUFRIEND_kbv library to interface with the display
    class Display_MCUFRIEND_kbv : public Gui900::Display
    {
    public:
        /// @brief Creates an instance of MCUFRIEND_kbv and uses it to interface with the screen.
        Display_MCUFRIEND_kbv(int id = 0);
        /// @brief Initializes the display. Only for internal use.
        /// @param orientation The orientation for the display.
        void init(Gui900::Orientation orientation);
        Adafruit_GFX &gfx();

    private:
        MCUFRIEND_kbv display;
        int id;
    };
}

#endif