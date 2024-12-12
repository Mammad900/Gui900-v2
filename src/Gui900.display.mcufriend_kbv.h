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

        void startPixelWrite(int x, int y, int w, int h)
        {
            pixelsWritten = 0;
            display.setAddrWindow(x, y, x + w - 1, y + h - 1);
        }
        void writePixels(uint16_t *block, int16_t n)
        {
            display.pushColors(block, n, pixelsWritten == 0);
            pixelsWritten += n;
        }
        void writePixels(const uint8_t *block, int16_t n)
        {
            display.pushColors((const uint8_t *)block, n, pixelsWritten == 0);
            pixelsWritten += n;
        }
        virtual void endPixelWrite()
        {
            pixelsWritten = 0;
            pw_x = -1;
            pw_y = -1;
            pw_w = 0;
            pw_h = 0;
            display.setAddrWindow(0, 0, display.width() - 1, display.height() - 1);
        }

    private:
        MCUFRIEND_kbv display;
        int id;
    };
}

#endif