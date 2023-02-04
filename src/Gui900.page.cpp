#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.page.h"

Gui900::Page::Page(App *app, uint16_t backColor) : backColor(backColor)
{
    this->app = app;
}

void Gui900::Page::draw(Adafruit_GFX &gfx, Page *previous)
{
    if (previous == NULL || previous->backColor != backColor)
        gfx.fillScreen(backColor);
    drawChildren(gfx);
}

void Gui900::Page::undraw(Adafruit_GFX &gfx)
{
    undrawChildren(gfx);
}

int Gui900::Page::getInnerWidth()
{
    return app->display.gfx().width();
}

int Gui900::Page::getInnerHeight()
{
    return app->display.gfx().height();
}
