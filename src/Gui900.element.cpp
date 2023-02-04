#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.element.h"

bool Gui900::Element::containsPoint(int x, int y)
{
    int absX = getAbsoluteX(), absY = getAbsoluteY();
    return x > absX && x < absX + width && y > absY && y < absY + height;
}

void Gui900::Container::addChild(Element *child)
{
    children.add(child);
    child->parent = this;
    child->app = app;
    if(isActive) {
        child->isActive = true;
        child->draw(app->display.gfx());
    }
}

void Gui900::Container::drawChildren(Adafruit_GFX &gfx)
{
    for (int i = 0; i < children.size(); i++)
    {
        Element *child = children[i];
        child->isActive = true;
        child->draw(gfx);
    }
}

void Gui900::Container::undrawChildren(Adafruit_GFX &gfx)
{
    for (int i = 0; i < children.size(); i++)
    {
        Element *child = children[i];
        child->undraw(gfx);
        child->isActive = false;
    }
}
