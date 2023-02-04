#ifndef __GUI900_PAGE_H__
#define __GUI900_PAGE_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.element.h"

namespace Gui900
{
    class Container;
    class App;

    /// @brief An app page/screen.
    class Page : public Container
    {
    public:
        /// @brief The background color of the page.
        uint16_t backColor;

        /// @brief Creates a new page
        /// @param app The app the page belongs to.
        /// @param backColor The background color of the page.
        Page(App *app, uint16_t backColor);

        /// @brief Draws the page on the screen (assuming the screen is blank), only for internal use.
        /// @param previous The page that was previously on the screen. Pass NULL if this is the first time a page is being drawn.
        void draw(Adafruit_GFX &gfx, Page *previous);

        /// @brief Cleans the screen so that only the background remains. Only for internal use.
        void undraw(Adafruit_GFX &gfx);

        int getContentAreaAbsoluteX() { return 0; }
        int getContentAreaAbsoluteY() { return 0; }
        int getInnerWidth();
        int getInnerHeight();
    };
}

#endif