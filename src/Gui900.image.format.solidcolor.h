#ifndef __GUI900_IMAGE_FORMAT_SOLIDCOLOR_H__
#define __GUI900_IMAGE_FORMAT_SOLIDCOLOR_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.image.h"

namespace Gui900
{
    namespace Image
    {
        namespace Formats
        {
            class SolidColor : public Format
            {
            public:
                uint16_t color;
                SolidColor(uint16_t color, int width, int height) : color(color)
                {
                    w = width;
                    h = height;
                }
                void draw(Gui900::Display &display, int x, int y)
                {
                    display.gfx().fillRect(x, y, w, h, color);
                }
            };
        }
    }
}

#endif /* __GUI900_IMAGE_FORMAT_SOLIDCOLOR_H__ */
