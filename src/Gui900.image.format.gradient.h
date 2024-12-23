#ifndef __GUI900_IMAGE_FORMAT_GRADIENT_H__
#define __GUI900_IMAGE_FORMAT_GRADIENT_H__

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
            /// @brief A linear gradient as an image. Only supports two colors, two directions and uses rgb interpolation.
            class Gradient : public Format
            {
            public:
                /// @brief Represents the direction of a linear gradient.
                enum Direction
                {
                    /// @brief Horizontal, from left to right.
                    left_right,
                    /// @brief Vertical, from top to bottom.
                    top_bottom,
                };

                /// @brief Starting color.
                uint16_t start;
                /// @brief Ending color.
                uint16_t end;
                /// @brief Gradient direction.
                Direction direction;

                /// @brief Creates a new gradient image.
                /// @param start Starting color
                /// @param end Ending color
                /// @param direction Gradient direction
                /// @param width Image width in pixels
                /// @param height Image height in pixels
                Gradient(uint16_t start, uint16_t end, Direction direction, int width, int height) : start(start), end(end), direction(direction)
                {
                    w = width;
                    h = height;
                }

                void draw(Gui900::Display &display, int x, int y)
                {
                    Adafruit_GFX &gfx = display.gfx();
                    switch (direction)
                    {
                    case left_right:
                        for (size_t i = 0; i < w; i++)
                        {
                            gfx.drawFastVLine(x + i, y, h, interpolateColor(start, end, i, w));
                        }
                        break;
                    case top_bottom:
                        for (size_t i = 0; i < h; i++)
                        {
                            gfx.drawFastHLine(x, y + i, w, interpolateColor(start, end, i, h));
                        }
                        break;

                    default:
                        break;
                    }
                }

            private:
                uint16_t interpolateColor(uint16_t colorA, uint16_t colorB, int pos, int max)
                {
                    // Extract a
                    uint8_t rA = (colorA >> 11) & 0x1F;
                    uint8_t gA = (colorA >> 5) & 0x3F;
                    uint8_t bA = colorA & 0x1F;

                    // extract b
                    uint8_t rB = (colorB >> 11) & 0x1F;
                    uint8_t gB = (colorB >> 5) & 0x3F;
                    uint8_t bB = colorB & 0x1F;

                    // actually interpolate
                    uint8_t r = rA + ((rB - rA) * pos / max);
                    uint8_t g = gA + ((gB - gA) * pos / max);
                    uint8_t b = bA + ((bB - bA) * pos / max);

                    // Combine channels
                    return (r << 11) | (g << 5) | b;
                }
            };
        }
    }
}

#endif /* __GUI900_IMAGE_FORMAT_GRADIENT_H__ */
