#ifndef __GUI900_UTIL_H__
#define __GUI900_UTIL_H__

#include <Arduino.h>
#include "Gui900.h"

namespace Gui900
{
    namespace Util
    {
        /// @brief Creates an RGB565 color.
        /// @param r The red component. From 0 to 255.
        /// @param g The green component. From 0 to 255.
        /// @param b The blue component. From 0 to 255.
        /// @return An RGB565 color.
        uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

        /// @brief Returns the start position of an object when centered in its container.
        /// @param containerSize The size of the container
        /// @param objectSize The size of the object
        int centerAlign(int containerSize, int objectSize);

        /// @brief Returns the end position of an object when centered in its container.
        /// @param containerSize The size of the container
        /// @param objectSize The size of the object
        int centerAlignEnd(int containerSize, int objectSize);
    }
}

#endif /* __GUI900_UTIL_H__ */
