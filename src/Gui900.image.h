#ifndef __GUI900_IMAGE_H__
#define __GUI900_IMAGE_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"

namespace Gui900
{
    namespace Image
    {
        /// @brief Decodes an image format and draws it. This class is abstract.
        class Format
        {
        public:
            int w, h;
            virtual void draw(Gui900::Display &display, int x, int y) = 0;
        };

        class Source
        {
        public:
            virtual void reset() = 0;
            virtual uint8_t read8() = 0;
            virtual uint16_t read16()
            {
                return read8() | read8() << 8;
            }
            virtual uint8_t *readBulk8(int n)
            {
                return NULL;
            }
            virtual uint16_t *readBulk16(int n)
            {
                return NULL;
            }
        };
    }
}

#endif /* __GUI900_IMAGE_H__ */
