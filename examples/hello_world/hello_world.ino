#include <Gui900.h>
#include <Gui900.display.mcufriend_kbv.h>
#include <Gui900.page.h>
#include <Gui900.element.label.h>
#include <Gui900.util.h>
#include <Fonts/FreeSans24pt7b.h>

using namespace Gui900; // Allow all identifiers inside Gui900 be accessed without needing to write Gui900:: every time
using namespace Gui900::Elements;

Display_MCUFRIEND_kbv tft; // Use MCUFRIEND_kbv as the display library
Input input; // Dummy input
App app(Orientation::landscape, tft, input);

Page mainPage(&app, Util::color565(0, 0, 0)); // Create the main page and use black as its background color

Label::Style *labelStyle = new Label::Style(
  Util::color565(255, 255, 255), // Foreground color
  &FreeSans24pt7b, // Font
  1 // Font size, optional
);

void setup() {
  mainPage.addChild(new Label(
    "Hello world", // Label text
    labelStyle, // Label style
    Util::centerAlign(240, 34), // Vertical style, replace 240 with your screen's width (height in landscape mode)
    Label::TextAlign::middle // Horizontal text alignment
  ));
  app.init(mainPage);
}

void loop() {
  // No loop code is needed because the app does nothing after starting
}
