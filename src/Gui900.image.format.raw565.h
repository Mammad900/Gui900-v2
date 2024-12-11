#ifndef __GUI900_IMAGE_FORMAT_RAW565_H__
#define __GUI900_IMAGE_FORMAT_RAW565_H__

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
            class Raw565 : public Format
            {
            public:
                Source &source;
                Raw565(Source &source, int width, int height) : source(source)
                {
                    w = width;
                    h = height;
                }
                void draw(Gui900::Display &display, int x, int y)
                {
                    source.reset();
                    display.startPixelWrite(x, y, w, h);
                    uint8_t *data = source.readAll();
                    const uint8_t *dataP = source.readAllProgmem();
                    if (data != NULL)
                    {
                        display.writePixels(data, w * h);
                    }
                    else if (dataP != NULL)
                    {
                        display.writePixels(dataP, w * h);
                    }
                    else
                    {
                        uint16_t color;
                        for (size_t i = 0; i < w * h; i++)
                        {
                            color = source.read16();
                            display.writePixels(&color, 1);
                        }
                    }
                    display.endPixelWrite();
                }
            };
        }
    }
}

#endif /* __GUI900_IMAGE_FORMAT_RAW565_H__ */
