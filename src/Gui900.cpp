#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Gui900.h"
#include "Gui900.page.h"

Gui900::App::App(Orientation orientation, Display &display, Input &input) : orientation(orientation), display(display), input(input)
{
    input.app = this;
}

void Gui900::App::init(Gui900::Page &startPage)
{
    display.init(orientation);
    currentPage = &startPage;
    startPage.isActive = true;
    startPage.draw(display.gfx(), NULL);
}

void Gui900::App::navigate(Gui900::Page &page)
{
    if (page.backColor == currentPage->backColor)
        currentPage->undraw(display.gfx());
    currentPage->isActive = false;
    page.isActive = true;
    page.draw(display.gfx(), currentPage);
    currentPage = &page;
}

void Gui900::App::update()
{
    input.update();
}

void Gui900::App::onPointerDown(int x, int y)
{
    if(currentPage != NULL) {
        for (int i = 0; i < currentPage->children.size(); i++)
        {
            Element *element = currentPage->children[i];
            element->onPointerDown(x, y);
        }
    }
}

void Gui900::App::onPointerUp(int x, int y)
{
    if(currentPage != NULL) {
        for (int i = 0; i < currentPage->children.size(); i++)
        {
            Element *element = currentPage->children[i];
            element->onPointerUp(x, y);
        }
    }
}

void Gui900::App::onPointerMove(int x, int y, bool isDown)
{
    if(currentPage != NULL) {
        for (int i = 0; i < currentPage->children.size(); i++)
        {
            Element *element = currentPage->children[i];
            element->onPointerMove(x, y, isDown);
        }
    }
}
