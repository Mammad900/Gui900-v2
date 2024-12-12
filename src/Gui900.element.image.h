#ifndef __GUI900_ELEMENT_IMAGE_H__
#define __GUI900_ELEMENT_IMAGE_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.h"
#include "Gui900.image.h"

namespace Gui900
{
    namespace Elements {
        /// @brief An image. Supports multiple formats and sources
        class Image : public Element {
            public:
                /// @brief The format of the image. Also includes the content
                Gui900::Image::Format &format;

                /// @brief Creates a new image element.
                /// @param x The position of the image relative to its parent's content area
                /// @param y The position of the image relative to its parent's content area
                /// @param format The source of the image with its format.
                Image(int x, int y, Gui900::Image::Format &format) : format(format) {
                    this->x = x;
                    this->y = y;
                    width = format.w;
                    height = format.h;
                }

                void draw(Adafruit_GFX &gfx) {
                    int absX = getAbsoluteX();
                    int absY = getAbsoluteY();
                    format.draw(app->display, absX, absY);
                }
                
                void undraw(Adafruit_GFX &gfx) {
                    int absX = getAbsoluteX();
                    int absY = getAbsoluteY();
                    gfx.fillRect(absX, absY, width, height, parent->backColor);
                }
        };
    }
}

#endif /* __GUI900_ELEMENT_IMAGE_H__ */
