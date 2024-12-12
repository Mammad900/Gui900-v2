#ifndef __GUI900_H__
#define __GUI900_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
// #include "Gui900.page.h"

namespace Gui900
{
    /// @brief A display orientation
    enum Orientation
    {
        /// @brief A rotation of 0 degrees from the native orientation of the display
        portrait,
        /// @brief A rotation of 90 degrees from the native orientation of the display
        landscape,
        /// @brief A rotation of 180 degrees from the native orientation of the display
        portrait_invert,
        /// @brief A rotation of 270 degrees from the native orientation of the display
        landscape_invert
    };

    class Page;

    /// @brief An interface for interacting with the display. This class is abstract.
    class Display
    {
    public:
        /// @brief Initializes the display
        /// @param orientation The orientation of the display
        virtual void init(Gui900::Orientation orientation) = 0;

        /// @brief Returns the Adafruit_GFX instance that can be used to draw to the screen
        virtual Adafruit_GFX &gfx() = 0;

        int pw_x = -1, pw_y = -1, pw_w = 0, pw_h = 0, pixelsWritten = 0;
        virtual void startPixelWrite(int x, int y, int w, int h) {
            pw_x = x;
            pw_y = y;
            pw_w = w;
            pw_h = h;
            pixelsWritten = 0;
        }
        virtual void writePixels(uint16_t *block, int16_t n) {
            if(pw_x == -1)
                return;
            Adafruit_GFX &g = gfx();
            for (size_t i = 0; i < n; i++)
            {
                int j = i + pixelsWritten;
                g.writePixel((j % pw_w) + pw_x, (j / pw_w) + pw_y, block[i]);
            }
            pixelsWritten += n;
        }
        virtual void writePixels(uint8_t *block, int16_t n) {
            writePixels((uint16_t *)block, n);
        }
        virtual void writePixels(const uint8_t *block, int16_t n){
            if(pw_x == -1)
                return;
            Adafruit_GFX &g = gfx();
            for (size_t i = 0; i < n; i++)
            {
                int j = i + pixelsWritten;
                g.writePixel((j % pw_w) + pw_x, (j / pw_w) + pw_y, pgm_read_word(&block[i]));
            }
            pixelsWritten += n;
        }
        virtual void endPixelWrite() {
            pw_x = -1;
            pw_y = -1;
            pw_w = 0;
            pw_h = 0;
            pixelsWritten = 0;
        }
    };

    class Input;

    /// @brief A Gui900 app
    class App
    {
    public:
        Page *currentPage;
        Display &display;
        Input &input;
        Orientation orientation;

        /// @brief Creates a new app.
        /// @param orientation The orientation of the display
        /// @param display An instance of Gui900::Display to use to draw to the screen
        /// @param input An instance of Gui900::Input to use to receive input.
        App(Orientation orientation, Display &display, Input &input);

        /// @brief Starts the app
        void init(Page &startPage);

        /// @brief Navigates to another page.
        /// @param page The page to navigate to
        void navigate(Page &page);

        /// @brief Checks for any events and performs other updates.
        void update();

        /// @brief Called by the input handler when the pointer is pressed.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        void onPointerDown(int x, int y);
        /// @brief Called by the input handler when the pointer is released.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        void onPointerUp(int x, int y);
        /// @brief Called by the input handler when the pointer moves.
        /// @param x The coordinates of the pointer
        /// @param y The coordinates of the pointer
        /// @param isDown Whether the pointer is currently being pressed.
        void onPointerMove(int x, int y, bool isDown);
    };

    /// @brief An interface for interacting with input devices (such as touch and mouse).
    class Input
    {
    public:
        virtual void update() { };
        App *app;
    };
}

#endif