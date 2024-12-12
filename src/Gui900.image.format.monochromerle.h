#ifndef __GUI900_IMAGE_FORMAT_MONOCHROMERLE_H__
#define __GUI900_IMAGE_FORMAT_MONOCHROMERLE_H__

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
            class MonochromeRLE : public Format
            {
            public:
                Source &source;
                uint16_t foreColor, backColor;
                MonochromeRLE(Source &source, uint16_t foreColor, uint16_t backColor, int width, int height) : source(source), foreColor(foreColor), backColor(backColor)
                {
                    w = width;
                    h = height;
                }
                void draw(Gui900::Display &display, int x, int y)
                {
                    source.reset();
                    display.startPixelWrite(x, y, w, h);
                    do
                    {
                        byte b1 = source.read8();
                        bool flag = (b1 & 0b10000000) >> 7;
                        int fore, back;
                        if (flag)
                        { // long run
                            fore = b1 & 0b01111111;
                            back = source.read8();
                        } else { // short run
                            fore = (b1 & 0b01110000) >> 4;
                            back = b1 & 0b00001111;
                        } 
                        for (size_t i = 0; i < fore; i++)
                        {
                            display.writePixels(&foreColor, 1);
                        }
                        for (size_t i = 0; i < back; i++)
                        {
                            display.writePixels(&backColor, 1);
                        }

                    } while (display.pixelsWritten < w * h);

                    display.endPixelWrite();
                }
            };
        }
    }
}

#endif /* __GUI900_IMAGE_FORMAT_MONOCHROMERLE_H__ */