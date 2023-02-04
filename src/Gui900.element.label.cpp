#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.util.h"
#include "Gui900.element.label.h"

Gui900::Elements::Label::Label(char *text, Style *style, int y, TextAlign align, int relativeX)
    : text(text), style(style), align(align), relativeX(relativeX)
{
    this->y = y;
    width = -1;
}

void Gui900::Elements::Label::draw(Adafruit_GFX &gfx)
{
    if (width == -1)
        calculateSize();
    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    gfx.setTextColor(style->color);
    gfx.setCursor(x, (style->font == NULL) ? y : y + height);
    gfx.print(text);
    // Too easy
}

void Gui900::Elements::Label::undraw(Adafruit_GFX &gfx)
{
    if (width == -1)
        calculateSize();
    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    gfx.setTextColor(parent->backColor);
    gfx.setCursor(x, (style->font == NULL) ? y : y + height);
    gfx.print(text);
}

void Gui900::Elements::Label::setStyle(Style *newStyle)
{
    if (isActive)
    {
        bool hasBigChanges =
            newStyle->font != style->font ||
            newStyle->fontSize != style->fontSize;
        if (hasBigChanges || newStyle->color != style->color) // Color is a small change (does not need deletion of previous drawings)
        {
            Adafruit_GFX &gfx = app->display.gfx();
            if (hasBigChanges)
                undraw(gfx);
            style = newStyle;
            calculateSize();
            draw(gfx);
        }
    }
    else
    {
        style = newStyle;
        calculateSize();
    }
}

void Gui900::Elements::Label::setText(const char *newText)
{
    if (isActive)
    {
        Adafruit_GFX &gfx = app->display.gfx();
        undraw(gfx);
        text = newText;
        calculateSize();
        draw(gfx);
    }
    else
    {
        text = newText;
        calculateSize();
    }
}

void Gui900::Elements::Label::calculateSize()
{
    Adafruit_GFX &gfx = app->display.gfx();
    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    int16_t x1, y1;
    uint16_t w, h;
    gfx.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    width = w;
    height = h;

    int x = 0;
    if (align == TextAlign::middle)
        x = Util::centerAlign(parent->getInnerWidth(), width);
    else if (align == TextAlign::right)
        x = parent->getInnerWidth() - width;
    x += relativeX;
    this->x = x;
}
