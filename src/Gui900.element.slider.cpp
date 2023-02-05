#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.element.slider.h"

Gui900::Elements::Slider::Slider(int x, int y, int width, Style *style, int minValue, int maxValue, int value)
    : style(style), minValue(minValue), maxValue(maxValue), value(value)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = style->height;
}

void Gui900::Elements::Slider::draw(Adafruit_GFX &gfx)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();
    int thumbWidth = style->thumbWidth;
    int borderRadius = style->borderRadius;
    int thumbRelativeX = map(value, minValue, maxValue, 0, width - thumbWidth);

    if (style->backColorStart != parent->backColor)
        gfx.fillRoundRect(absX,
                          absY,
                          thumbRelativeX + thumbWidth,
                          height,
                          borderRadius,
                          style->backColorStart); // Start

    if (style->backColorEnd != parent->backColor)
        gfx.fillRoundRect(absX + thumbRelativeX,
                          absY,
                          width - thumbRelativeX,
                          height,
                          borderRadius,
                          style->backColorEnd); // End

    gfx.fillRoundRect(absX + thumbRelativeX,
                      absY,
                      thumbWidth,
                      height,
                      borderRadius,
                      style->thumbColor); // Thumb

    if (style->hasBorder)
        gfx.drawRoundRect(absX, absY, width, height, borderRadius, style->borderColor); // Border
}

void Gui900::Elements::Slider::undraw(Adafruit_GFX &gfx)
{
    gfx.fillRect(getAbsoluteX(), getAbsoluteY(), width, height, parent->backColor);
}

void Gui900::Elements::Slider::setValue(int value)
{
    if (this->value == value)
        return;

    if (isActive)
    {
        Adafruit_GFX &gfx = app->display.gfx();
        int absX = getAbsoluteX();
        int absY = getAbsoluteY();
        int thumbWidth = style->thumbWidth;
        int borderRadius = style->borderRadius;
        int thumbXOld = map(this->value, minValue, maxValue, 0, width - thumbWidth);
        int thumbXNew = map(value, minValue, maxValue, 0, width - thumbWidth);

        if (this->value > value) // Decreased
        {
            gfx.fillRoundRect(absX + thumbXNew,
                              absY,
                              thumbXOld - thumbXNew + thumbWidth,
                              height,
                              borderRadius,
                              style->backColorEnd);
        }
        else // Increased
        {
            gfx.fillRoundRect(absX + thumbXOld,
                              absY,
                              thumbXNew - thumbXOld + thumbWidth,
                              height,
                              borderRadius,
                              style->backColorStart);
        }

        gfx.fillRoundRect(absX + thumbXNew,
                          absY,
                          thumbWidth,
                          height,
                          borderRadius,
                          style->thumbColor); // Thumb

        if (style->hasBorder)
            gfx.drawRoundRect(absX, absY, width, height, borderRadius, style->borderColor); // Border
    }

    this->value = value;
}

bool Gui900::Elements::Slider::containsPoint(int x, int y)
{
    int absX = getAbsoluteX() - 10, absY = getAbsoluteY() - 10;
    int width = this->width + 20;
    int height = this->height + 20; // Increase click area by 10px in each direction
    return x > absX && x < absX + width && y > absY && y < absY + height;
}

void Gui900::Elements::Slider::onPointerDown(int x, int y)
{
    if(containsPoint(x, y)) {
        isDown = true;
    }
}

void Gui900::Elements::Slider::onPointerUp(int x, int y)
{
    isDown = false;
}

void Gui900::Elements::Slider::onPointerMove(int x, int y, bool down)
{
    if(isDown)
    {
        x -= getAbsoluteX(); // Get relative position
        y -= getAbsoluteY();

        int thumbWidth = style->thumbWidth;
        int newValue = map(x, thumbWidth / 2, width - thumbWidth / 2, minValue, maxValue);
        setValue(constrain(newValue, minValue, maxValue));
    }
}
