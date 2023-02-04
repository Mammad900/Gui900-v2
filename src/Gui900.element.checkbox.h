#ifndef __GUI900_ELEMENT_CHECKBOX_H__
#define __GUI900_ELEMENT_CHECKBOX_H__

#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.h"

namespace Gui900
{
    namespace Elements
    {
        /// @brief A switchable check box
        class CheckBox : public Element
        {
        public:
            /// @brief Represents the style of a check box
            struct Style
            {
                /// @brief Check box background color
                uint16_t boxBackColor;
                /// @brief Check box border color
                uint16_t boxBorderColor;
                /// @brief Check mark color
                uint16_t checkMarkColor;
                /// @brief Label foreground color
                uint16_t labelColor;
                /// @brief Check box size, in pixels
                int size;
                /// @brief How rounded the check box corners are
                int borderRadius;
                /// @brief Label font
                const GFXfont *font;
                /// @brief The height of the label
                int lineHeight;
                /// @brief Label font size multiplier, causes text to become blocky.
                int fontSize;
                /// @brief The space between the box and the label
                int margin;

                /// @brief Creates a new check box style.
                /// @param boxBackColor Box background color
                /// @param boxBorderColor Box border color
                /// @param checkMarkColor Check mark color
                /// @param labelColor Label foreground color
                /// @param size Box size, in pixels
                /// @param borderRadius How rounded the box corners are
                /// @param font Label font
                /// @param lineHeight Label line height. Increase if the text is too high, decrease if the text is too low. Set to 0 to automatically infer. Ignored for the default (NULL) font.
                /// @param fontSize Label font size multiplier, causes text to become blocky.
                /// @param margin The space between the box and the label
                Style(
                    uint16_t boxBackColor = 0x630C,
                    uint16_t boxBorderColor = 0x630C,
                    uint16_t checkMarkColor = 0xFFFF,
                    uint16_t labelColor = 0xFFFF,
                    int size = 30,
                    int borderRadius = 5,
                    const GFXfont *font = NULL,
                    int lineHeight = 0,
                    int fontSize = 2,
                    int margin = 10)
                    : boxBackColor(boxBackColor),
                      boxBorderColor(boxBorderColor),
                      checkMarkColor(checkMarkColor),
                      labelColor(labelColor),
                      size(size),
                      borderRadius(borderRadius),
                      font(font),
                      lineHeight(lineHeight),
                      fontSize(fontSize),
                      margin(margin)
                {
                }
            };

            /// @brief Contains different styles for different check box states.
            struct Styles
            {
                Style *normal, *hover, *active;

                Styles(Style *normal, Style *hover = NULL, Style *active = NULL)
                    : normal(normal), hover(hover), active(active) {}
            };

            /// @brief The way a check box should be toggled
            enum ToggleBehavior
            {
                /// @brief The check box is toggled when the pointer is pressed inside the check box
                down,
                /// @brief The check box is toggled when the pointer is both pressed and released inside the check box.
                up
            };

            /// @brief Check box label text
            char *label;
            /// @brief The style currently in use
            Style *style;
            /// @brief The styles to use for the check box
            Styles *styles;
            /// @brief Called when the check box is switched
            void (*onChange)(CheckBox *);
            /// @brief The way the button should be clicked
            ToggleBehavior toggleBehavior;
            /// @brief Whether the checkbox is currently checked
            bool isChecked;

            /// @brief Creates a new check box.
            /// @param x The position of the check box relative to its parent's content area
            /// @param y The position of the check box relative to its parent's content area
            /// @param text Label text
            /// @param onChange The function to call when the checkbox is toggled
            /// @param styles Check box styles
            /// @param isChecked Whether the check box is initially checked
            /// @param toggleBehavior The way the check box should be clicked to toggle it
            CheckBox(
                int x, int y,
                char *label,
                void (*onChange)(CheckBox *),
                Styles *styles,
                bool isChecked = false,
                ToggleBehavior toggleBehavior = ToggleBehavior::up);

            void draw(Adafruit_GFX &gfx);
            void undraw(Adafruit_GFX &gfx);

            void onPointerDown(int x, int y);
            void onPointerUp(int x, int y);
            bool containsPoint(int x, int y);

            /// @brief Changes the style to a new one.
            /// @param newStyle The new style
            void setStyle(Style *newStyle);

        private:
            void drawBox(Adafruit_GFX &gfx);
            void drawCheck(Adafruit_GFX &gfx, bool undraw = false);
            void drawLabel(Adafruit_GFX &gfx, bool undraw = false);
            bool isHolding;
            bool isHover;
            void onClick();
            void calculateSize();
        };
    }
}

#endif /* __GUI900_ELEMENT_CHECKBOX_H__ */
