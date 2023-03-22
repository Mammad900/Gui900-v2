#include <Gui900.h>
#include <Gui900.display.mcufriend_kbv.h>
#include <Gui900.input.touch.h>
#include <Gui900.page.h>
#include <Gui900.element.label.h>
#include <Gui900.util.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

using namespace Gui900; // Allow all identifiers inside Gui900 be accessed without needing to write Gui900:: every time
using namespace Gui900::Elements;

Display_MCUFRIEND_kbv tft; // Use MCUFRIEND_kbv as the display library
TouchInput touch(6, A2, A1, 7, 950, 100, 100, 944, 10, 1000); // You need to run the Touchscreen_calibr_native example from MCUFRIEND_kbv to get calibration values for your own screen.
App app(Orientation::portrait, tft, touch);

Page mainPage(&app, Util::color565(0, 0, 0)); // Create the main page and use black as its background color

Label::Style *style1 = new Label::Style(0xFFFF);
Label::Style *style2 = new Label::Style(TFT_GREEN, &FreeSans9pt7b);
Label::Style *style3 = new Label::Style(Util::color565(128, 128, 128), &FreeSans9pt7b);
// Label::Style *style

void setup() {
    // Parameters in order: Text, style, Y, [alignment], [delta X]
    mainPage.addChild(new Label("This is a label", style1, 10, Label::TextAlign::left, 10));
    mainPage.addChild(new Label("This is also a label", style2, 30, Label::TextAlign::left, 10));
    mainPage.addChild(new Label("Labels can be aligned:", style3, 50, Label::TextAlign::left, 10));
    mainPage.addChild(new Label("Left", style3, 70, Label::TextAlign::left, 10));
    mainPage.addChild(new Label("Center", style3, 70, Label::TextAlign::middle));
    mainPage.addChild(new Label("Right", style3, 70, Label::TextAlign::right, -10));

    app.init(mainPage);
}

void loop() {
  app.update();
}
