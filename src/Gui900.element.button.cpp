#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.util.h"
#include "Gui900.element.button.h"

Gui900::Elements::Button::Button(int x, int y, int w, int h, const char *text, Styles *styles, void (*onClick)(Button *), ClickBehavior clickBehavior)
    : text(text), styles(styles), onClick(onClick), clickBehavior(clickBehavior)
{
    this->x = x;
    this->y = y;
    width = w;
    height = h;
    style = styles->normal;
}

void Gui900::Elements::Button::onPointerDown(int x, int y)
{
    bool isHoverNow = containsPoint(x, y);
    if (isHoverNow && !isHover)
        setStyle(styles->active != NULL ? styles->active : styles->normal);
    isHover = isHoverNow;
    if (isHover)
    {
        if (clickBehavior == ClickBehavior::up)
            isHolding = true;
        else if (onClick != NULL)
            onClick(this);
    }
}

void Gui900::Elements::Button::onPointerUp(int x, int y)
{
    if (isHover)
        setStyle(styles->normal);
    isHover = false;
    if (isHolding && clickBehavior == ClickBehavior::up)
    {
        if (containsPoint(x, y) && onClick != NULL)
        {
            onClick(this);
        }
        isHolding = false;
    }
}

void Gui900::Elements::Button::draw(Adafruit_GFX &gfx)
{
    draw(gfx, false);
}

void Gui900::Elements::Button::draw(Adafruit_GFX &gfx, bool force)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();
    if (style->backColor != parent->backColor || force)
        gfx.fillRoundRect(absX, absY, width, height, style->borderRadius, style->backColor);
    if (style->backColor != style->borderColor || force)
        gfx.drawRoundRect(absX, absY, width, height, style->borderRadius, style->borderColor);
    if (strlen(text) > 0)
    {
        drawText(gfx);
    }
}

void Gui900::Elements::Button::undraw(Adafruit_GFX &gfx)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();
    gfx.fillRect(absX, absY, width, height, parent->backColor);
}

void Gui900::Elements::Button::setStyle(Style *newStyle)
{
    if (isActive)
    {
        // Warning: Complex code ahead

        Adafruit_GFX &gfx = app->display.gfx();
        int absX = getAbsoluteX();
        int absY = getAbsoluteY();

        int r = newStyle->borderRadius;
        if (r != style->borderRadius)
        {
            if (newStyle->backColor != parent->backColor || style->backColor != parent->backColor) // Redraw everything
            {
                if (r > style->borderRadius) // If the new border radius is bigger, the new drawing won't cover the existing drawing so we need to delete some parts.
                {
                    gfx.fillRect(absX, absY, r, r, parent->backColor);                          // Top left
                    gfx.fillRect(absX + width - r, absY, r, r, parent->backColor);              // Top right
                    gfx.fillRect(absX + width - r, absY + height - r, r, r, parent->backColor); // Bottom right
                    gfx.fillRect(absX, absY + height - r, r, r, parent->backColor);             // Bottom left
                }
                style = newStyle;
                draw(gfx, true);
                return;
            }
            else // Transparent background, only redraw border.
            {
                gfx.drawRoundRect(absX, absY, width, height, style->borderRadius, parent->backColor); // Delete previous border
                gfx.drawRoundRect(absX, absY, width, height, r, newStyle->borderColor);               // Draw new border
            }
        }
        else
        {
            if (newStyle->backColor != style->backColor)
            {
                style = newStyle;
                draw(gfx, true); // Redraw everything
                return;
            }
            else if (newStyle->borderColor != style->borderColor)
            {
                gfx.drawRoundRect(absX, absY, width, height, r, newStyle->borderColor); // Draw new border
            }
        }
        if (newStyle->font != style->font ||
            newStyle->lineHeight != style->lineHeight ||
            newStyle->fontSize != style->fontSize)
        {
            drawText(gfx, true); // Delete previous text
            style = newStyle;
            drawText(gfx);
            return;
        }
        if (newStyle->foreColor != style->foreColor)
        {
            style = newStyle;
            drawText(gfx);
        }
    }
    style = newStyle;
}

void Gui900::Elements::Button::drawText(Adafruit_GFX &gfx, bool undraw)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();

    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    gfx.setTextColor(undraw ? style->backColor : style->foreColor);
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    gfx.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    if (style->font != NULL)
    {
        textHeight = style->lineHeight > 0 ? style->lineHeight : style->font->yAdvance * style->fontSize * 0.5;
    }
    gfx.setCursor(
        Util::centerAlign(width, textWidth) + absX,
        ((style->font == NULL) ? Util::centerAlign(height, textHeight) : Util::centerAlignEnd(height, textHeight)) + absY); // The NULL font has the baseline at the top, other fonts have baseline at the bottom.
    gfx.print(text);
}
