#ifndef __GUI900_ELEMENT_SLIDER_H__
#define __GUI900_ELEMENT_SLIDER_H__

#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.h"

namespace Gui900
{
    namespace Elements
    {
        /// @brief A slider
        class Slider : public Element
        {
        public:
            /// @brief Represents the style of a slider.
            struct Style
            {
                /// @brief The background color of the track from minimum value to thumb
                uint16_t backColorStart;
                /// @brief The background color of the track from thumb to maximum value
                uint16_t backColorEnd;
                /// @brief Whether the track has a border
                bool hasBorder;
                /// @brief Track border color, if present
                uint16_t borderColor;
                /// @brief Thumb fill color
                uint16_t thumbColor;
                /// @brief Slider height. Should not change for the same slider as it will not be re-rendered.
                int height;
                /// @brief Thumb width
                int thumbWidth;
                /// @brief How rounded track and thumb corners are
                int borderRadius;

                /// @brief Creates a new slider style
                /// @param backColorStart The background color of the track from minimum value to thumb
                /// @param backColorEnd The background color of the track from thumb to maximum value
                /// @param hasBorder Whether the track has a border
                /// @param borderColor Track border color, if present
                /// @param thumbColor Thumb fill color
                /// @param height Slider height. Should not change for the same slider as it will not be re-rendered.
                /// @param thumbWidth Thumb width
                Style(uint16_t backColorStart = 0x630C,
                      uint16_t backColorEnd = 0x630C,
                      bool hasBorder = false,
                      uint16_t borderColor = 0xFFFF,
                      uint16_t thumbColor = 0xFFFF,
                      int height = 14,
                      int thumbWidth = 14,
                      int borderRadius = 7)
                    : backColorStart(backColorStart),
                      backColorEnd(backColorEnd),
                      hasBorder(hasBorder),
                      borderColor(borderColor),
                      thumbColor(thumbColor),
                      height(height),
                      thumbWidth(thumbWidth),
                      borderRadius(borderRadius)
                {
                }
            };

            /// @brief The style to use in the slider
            Style *style;
            /// @brief The minimum value the slider can have
            int minValue;
            /// @brief The maximum value the slider can have
            int maxValue;
            /// @brief The current value
            int value;

            /// @brief Creates a new slider
            /// @param x The position of the slider relative to its parent.
            /// @param y The position of the slider relative to its parent.
            /// @param width Slider width
            /// @param style The style to use in the slider
            /// @param min The minimum value the slider can have
            /// @param max The maximum value the slider can have
            /// @param value The initial value
            Slider(int x, int y, int width, Style *style, int minValue = 0, int maxValue = 100, int value = 0);

            void draw(Adafruit_GFX &gfx);
            void undraw(Adafruit_GFX &gfx);

            /// @brief Changes the value of the slider.
            void setValue(int value);

            void onPointerDown(int x, int y);
            void onPointerUp(int x, int y);
            void onPointerMove(int x, int y, bool down);
            bool containsPoint(int x, int y);

        private:
            bool isDown;
        };
    }
}

#endif /* __GUI900_ELEMENT_SLIDER_H__ */
