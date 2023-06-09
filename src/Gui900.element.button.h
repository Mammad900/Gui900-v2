#ifndef __GUI900_ELEMENT_BUTTON_H__
#define __GUI900_ELEMENT_BUTTON_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.h"

namespace Gui900
{
    namespace Elements
    {
        /// @brief A clickable button.
        class Button : public Gui900::Element
        {
        public:
            /// @brief Represents the style of the button
            struct Style
            {
                static const uint16_t defaultBackColor = 0x630C;
                static const uint16_t defaultForeColor = 0xFFFF;
                static const uint16_t defaultBorderColor = defaultBackColor;
                static const uint16_t defaultBorderColorHover = 0xA534;
                static const uint16_t defaultBorderColorActive = 0xFFFF;
                static const int defaultBorderRadius = 5;

                /// @brief The background color
                uint16_t backColor;
                /// @brief The text color
                uint16_t foreColor;
                /// @brief The border color
                uint16_t borderColor;
                /// @brief How rounded the corners are
                int borderRadius;
                /// @brief The font for the text
                const GFXfont *font;
                /// @brief Font size multiplier. Causes text to become blocky
                int fontSize;
                /// @brief The height of the text.
                int lineHeight;

                /// @brief Creates a new button style
                /// @param backColor The background color
                /// @param foreColor The text color
                /// @param borderColor The border color
                /// @param borderRadius How rounded the corners are
                /// @param font The font for the text
                /// @param lineHeight The height of the text. Increase if the text is too high, decrease if the text is too low. Set to 0 to automatically infer. Ignored for the default (NULL) font.
                /// @param fontSize Font size multiplier. Causes text to become blocky.
                Style(
                    uint16_t backColor = defaultBackColor,
                    uint16_t foreColor = defaultForeColor,
                    uint16_t borderColor = defaultBorderColor,
                    int borderRadius = defaultBorderRadius,
                    const GFXfont *font = NULL,
                    int lineHeight = 0,
                    int fontSize = 2)
                    : backColor(backColor),
                      foreColor(foreColor),
                      borderColor(borderColor),
                      borderRadius(borderRadius),
                      font(font),
                      lineHeight(lineHeight),
                      fontSize(fontSize)
                {
                }

                static Style *fromFont(
                    const GFXfont *font,
                    int lineHeight = 0,
                    int fontSize = 1)
                {
                    return new Style(
                        defaultBackColor,
                        defaultForeColor,
                        defaultBorderColor,
                        defaultBorderRadius,
                        font,
                        lineHeight,
                        fontSize);
                }
            };

            /// @brief Contains different styles for different button states.
            struct Styles
            {
                Style *normal, *hover, *active;

                /// @brief Creates a new Styles object.
                /// @param normal The style to use by default
                /// @param hover The style to use when the pointer is over the button but is not pressed (pass NULL for touch screen apps)
                /// @param active The style to use when the pointer is over the button and is pressed
                Styles(Style *normal, Style *hover = NULL, Style *active = NULL)
                    : normal(normal), hover(hover), active(active) {}

                /// @brief Creates a Styles object from the default button style.
                Styles()
                {
                    normal = new Style();
                    hover = new Style(Style::defaultBackColor, Style::defaultForeColor, Style::defaultBorderColorHover);
                    active = new Style(Style::defaultBackColor, Style::defaultForeColor, Style::defaultBorderColorActive);
                }

                static Styles *fromFont(
                    const GFXfont *font,
                    int lineHeight = 0,
                    int fontSize = 1)
                {
                    return new Styles(
                        new Style(
                            Style::defaultBackColor,
                            Style::defaultForeColor,
                            Style::defaultBorderColor,
                            Style::defaultBorderRadius,
                            font,
                            lineHeight,
                            fontSize),
                        new Style(
                            Style::defaultBackColor,
                            Style::defaultForeColor,
                            Style::defaultBorderColorHover,
                            Style::defaultBorderRadius,
                            font,
                            lineHeight,
                            fontSize),
                        new Style(
                            Style::defaultBackColor,
                            Style::defaultForeColor,
                            Style::defaultBorderColorActive,
                            Style::defaultBorderRadius,
                            font,
                            lineHeight,
                            fontSize) );
                }
            };

            /// @brief The way a button should be clicked
            enum ClickBehavior
            {
                /// @brief The click is triggered when the pointer is pressed inside the button
                down,
                /// @brief The click is triggered when the pointer is both pressed and released inside the button.
                up
            };

            /// @brief The text to display on the button
            const char *text;
            /// @brief The style currently in use
            Style *style;
            /// @brief The styles to use for the button
            Styles *styles;
            /// @brief Called when the button is clicked
            void (*onClick)(Button *);
            /// @brief The way the button should be clicked
            ClickBehavior clickBehavior;

            /// @brief Creates a new button.
            /// @param x The position of the button relative to its parent's content area
            /// @param y The position of the button relative to its parent's content area
            /// @param w The width of the button
            /// @param h The height of the button
            /// @param text The text to display on the button
            /// @param styles Button styles
            /// @param onClick The function to call when the button is pressed.
            /// @param clickBehavior The way the button should be clicked to trigger onClick.
            Button(int x, int y, int w, int h, const char *text, Styles *styles, void (*onClick)(Button *), ClickBehavior clickBehavior = ClickBehavior::up);

            void onPointerDown(int x, int y);
            void onPointerUp(int x, int y);

            void draw(Adafruit_GFX &gfx);
            void draw(Adafruit_GFX &gfx, bool force);
            void undraw(Adafruit_GFX &gfx);

            /// @brief Changes the style to a new one.
            /// @param style The new style.
            void setStyle(Style *newStyle);

        private:
            void drawText(Adafruit_GFX &gfx, bool undraw = false);
            bool isHolding;
            bool isHover;
        };
    }
}

#endif /* __GUI900_ELEMENT_BUTTON_H__ */
