#include <Arduino.h>
#include <TouchScreen.h>
#include "Gui900.h"
#include "Gui900.input.touch.h"

bool Gui900::TouchInput::Touch_getXY()
{
    // This function was taken from the Touch_shield_new example from the MCUFRIEND_kbv library and modified.

    int scrWidth = app->display.gfx().width();
    int scrHeight = app->display.gfx().height();

    TSPoint tp = screen->getPoint(); // Read the touch

    // If sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);

    // We have some minimum pressure we consider 'valid'
    // Pressure of 0 means no pressing!
    bool touch = tp.z > minPressure && tp.z < maxPressure;

    // Debounce touch
    // If last detected touch was at most 100ms ago, it is still being touched.
    unsigned long now = millis();
    if (touch)
        lastTouch = now;
    if ((!touch) && ((now - lastTouch) < 100))
        return true;

    // Now map the coordinates and update the vars
    if (touch)
    {
        pixelZ = tp.z;

        // Calibration is true for PORTRAIT. tp.y is always long dimension
        // Map to your current pixel orientation
        switch (app->orientation)
        {
        case portrait:
            pixelX = map(tp.x, tsLeft, tsRight, 0, scrWidth);
            pixelY = map(tp.y, tsTop, tsBottom, 0, scrHeight);
            break;
        case landscape:
            pixelX = map(tp.y, tsTop, tsBottom, 0, scrWidth);
            pixelY = map(tp.x, tsRight, tsLeft, 0, scrHeight);
            break;
        case portrait_invert:
            pixelX = map(tp.x, tsRight, tsLeft, 0, scrWidth);
            pixelY = map(tp.y, tsBottom, tsTop, 0, scrHeight);
            break;
        case landscape_invert:
            pixelX = map(tp.y, tsBottom, tsTop, 0, scrWidth);
            pixelY = map(tp.x, tsLeft, tsRight, 0, scrHeight);
            break;
        }
        return true;
    }
    return false; // Wasn't pressed.
}

Gui900::TouchInput::TouchInput(
    int XP, int XM, int YP, int YM,
    int tsLeft, int tsRight, int tsTop, int tsBottom,
    int minPressure, int maxPressure)
    : XP(XP), XM(XM), YP(YP), YM(YM),
      tsLeft(tsLeft), tsRight(tsRight), tsTop(tsTop), tsBottom(tsBottom),
      minPressure(minPressure), maxPressure(maxPressure)
{
    screen = new TouchScreen(XP, YP, XM, YM, 300);
}

void Gui900::TouchInput::update()
{
    int prevPixelX = pixelX, prevPixelY = pixelY;
    bool isPressed = !Touch_getXY();
    if (isPressed && !this->isPressed)
    {
        app->onPointerUp(pixelX, pixelY);
    }
    if (this->isPressed && !isPressed)
    {
        app->onPointerDown(pixelX, pixelY);
    }
    if ((!isPressed) && (prevPixelX != pixelX || prevPixelY != pixelX))
    {
        app->onPointerMove(pixelX, pixelY, isPressed);
    }
    this->isPressed = isPressed;
}
