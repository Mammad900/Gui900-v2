#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.util.h"
#include "Gui900.element.checkbox.h"

Gui900::Elements::CheckBox::CheckBox(
    int x, int y,
    char *label,
    void (*onChange)(CheckBox *),
    Styles *styles,
    bool isChecked,
    ToggleBehavior toggleBehavior)
    : label(label),
      onChange(onChange),
      styles(styles),
      toggleBehavior(toggleBehavior)
{
    this->x = x;
    this->y = y;
    style = styles->normal;
    height = style->size;
    width = -1;
}

void Gui900::Elements::CheckBox::draw(Adafruit_GFX &gfx)
{
    if(width == -1)
        calculateSize();
    drawBox(gfx);
    if (strlen(label) > 0)
        drawLabel(gfx);
}

void Gui900::Elements::CheckBox::undraw(Adafruit_GFX &gfx)
{
    if(width == -1)
        calculateSize();
    gfx.fillRect(getAbsoluteX(), getAbsoluteY(), style->size, style->size, parent->backColor);
    drawLabel(gfx, true);
}

void Gui900::Elements::CheckBox::setStyle(Style *newStyle)
{
    if (isActive)
    {
        Adafruit_GFX &gfx = app->display.gfx();
        int absX = getAbsoluteX();
        int absY = getAbsoluteY();
        Style *oldStyle = style;

        bool textHadBigChange = // Need to undraw & redraw & recalculate size
            newStyle->font != style->font ||
            newStyle->fontSize != style->fontSize ||
            newStyle->lineHeight != style->lineHeight ||
            newStyle->size != style->size || // Affects position
            newStyle->margin != style->margin;

        if (textHadBigChange) {
            calculateSize();
            drawLabel(gfx, true); // Undraw
        }

        if (newStyle->borderRadius != style->borderRadius ||
            newStyle->boxBackColor != style->boxBackColor ||
            newStyle->size != style->size)
        {
            style = newStyle;
            drawBox(gfx);
        }
        else
        {
            if (newStyle->boxBorderColor != style->boxBorderColor)
            {
                gfx.drawRoundRect(absX, absY, newStyle->size, newStyle->size, newStyle->borderRadius, newStyle->boxBorderColor);
            }
            if (newStyle->checkMarkColor != style->checkMarkColor)
            {
                style = newStyle;
                drawCheck(gfx);
            }
        }
        style = newStyle;

        if (textHadBigChange || newStyle->labelColor != oldStyle->labelColor)
            drawLabel(gfx);
    }
    style = newStyle;
}

void Gui900::Elements::CheckBox::drawBox(Adafruit_GFX &gfx)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();
    int size = style->size;

    if (style->boxBackColor != parent->backColor)
        gfx.fillRoundRect(absX, absY, size, size, style->borderRadius, style->boxBackColor);
    if (style->boxBorderColor != style->boxBackColor)
        gfx.drawRoundRect(absX, absY, size, size, style->borderRadius, style->boxBorderColor);

    if (isChecked)
        drawCheck(gfx);
}

void Gui900::Elements::CheckBox::drawCheck(Adafruit_GFX &gfx, bool undraw)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();
    int size = style->size;
    uint16_t color = undraw ? style->boxBackColor : style->checkMarkColor;

    gfx.drawLine(absX + size * 0.15, absY + size * 0.55,
                 absX + size * 0.35, absY + size * 0.75,
                 color);
    gfx.drawLine(absX + size * 0.35, absY + size * 0.75,
                 absX + size * 0.85, absY + size * 0.25,
                 color);
}

void Gui900::Elements::CheckBox::drawLabel(Adafruit_GFX &gfx, bool undraw)
{
    int absX = getAbsoluteX();
    int absY = getAbsoluteY();

    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    gfx.setTextColor(undraw ? parent->backColor : style->labelColor);

    int textY;
    if (style->font == NULL)
        textY = absY + Util::centerAlign(style->size, 8 /*Default font height*/ * style->fontSize);
    else
        textY = absY + ((style->lineHeight == 0) ? Util::centerAlignEnd(style->size, style->font->yAdvance * style->fontSize * 0.5) : style->lineHeight);
    gfx.setCursor(absX + style->size + style->margin, textY);

    gfx.print(label);
}

void Gui900::Elements::CheckBox::onClick()
{
    if(isChecked)
        isChecked = false;
    else
        isChecked = true;
    // I tried `isChecked = !isChecked;` but it didn't work. I don't know why.

    if (isActive) // This method cannot be triggered if it is false, but I'll put this here in case it does
        drawCheck(app->display.gfx(), !isChecked);
    if (onChange != NULL)
        onChange(this);
}

void Gui900::Elements::CheckBox::onPointerDown(int x, int y)
{
    bool isHoverNow = containsPoint(x, y);
    if (isHoverNow && !isHover)
        setStyle(styles->active != NULL ? styles->active : styles->normal);
    isHover = isHoverNow;
    if (isHover)
    {
        if (toggleBehavior == ToggleBehavior::up)
            isHolding = true;
        else
            onClick();
    }
}

void Gui900::Elements::CheckBox::onPointerUp(int x, int y)
{
    if (isHover)
        setStyle(styles->normal);
    isHover = false;
    if (isHolding && toggleBehavior == ToggleBehavior::up)
    {
        if (containsPoint(x, y))
        {
            onClick();
        }
        isHolding = false;
    }
}

bool Gui900::Elements::CheckBox::containsPoint(int x, int y)
{
    int absX = getAbsoluteX() - 10, absY = getAbsoluteY() - 10;
    int width = this->width + 20;
    int height = this->height + 20; // Increase click area by 10px in each direction
    return x > absX && x < absX + width && y > absY && y < absY + height;
}

void Gui900::Elements::CheckBox::calculateSize()
{
    Adafruit_GFX &gfx = app->display.gfx();
    gfx.setFont(style->font);
    gfx.setTextSize(style->fontSize);
    int16_t x1, y1;
    uint16_t w, h;
    gfx.getTextBounds(label, 0, 0, &x1, &y1, &w, &h);
    width = style->size + style->margin + w;
}