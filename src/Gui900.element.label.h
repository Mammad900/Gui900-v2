#ifndef __GUI900_ELEMENT_LABEL_H__
#define __GUI900_ELEMENT_LABEL_H__

#include <arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.h"

namespace Gui900
{
    namespace Elements
    {
        /// @brief A label for informational purposes. Multiline text is not supported.
        class Label : public Gui900::Element
        {
        public:
            /// @brief Represents the style of a label
            struct Style
            {
                /// @brief Label font
                const GFXfont *font;
                /// @brief Font size multiplier. Causes text to become blocky.
                int fontSize;
                /// @brief Text color
                uint16_t color;

                /// @brief Creates a new label style
                /// @param font Label font
                /// @param fontSize Font size multiplier. Causes text to become blocky.
                /// @param color Text color
                Style(uint16_t color, const GFXfont *font = NULL, int fontSize = 1)
                    : font(font), fontSize(fontSize), color(color) {}
            };

            /// @brief Represents the alignment of a label.
            enum TextAlign
            {
                left,
                middle,
                right
            };

            /// @brief The style used for the label
            Style *style;
            /// @brief Label text
            char *text;
            /// @brief Text alignment relative to the parent
            TextAlign align;
            /// @brief The relative horizontal position of the label after applying the alignment
            int relativeX;

            /// @brief Creates a new label.
            /// @param text Label text
            /// @param style Label style
            /// @param y The vertical position of the label relative to the parent.
            /// @param align Text alignment relative to the parent
            /// @param relativeX Relative horizontal position after applying the alignment
            Label(char *text, Style *style, int y, TextAlign align = TextAlign::left, int relativeX = 0);

            void draw(Adafruit_GFX &gfx);
            void undraw(Adafruit_GFX &gfx);

            /// @brief Applies a new style.
            /// @param newStyle The new style
            void setStyle(Style *newStyle);

            /// @brief Changes the text of the label.
            void setText(const char *newText);

            ~Label();

        private:
            void calculateSize();
        };
    }
}

#endif /* __GUI900_ELEMENT_LABEL_H__ */
