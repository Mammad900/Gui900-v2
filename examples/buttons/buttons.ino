#include <Gui900.h>
#include <Gui900.display.mcufriend_kbv.h>
#include <Gui900.input.touch.h>
#include <Gui900.page.h>
#include <Gui900.element.button.h>
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

Button::Styles *style1 = new Button::Styles(); // Default style
Button::Styles *style2 = Button::Styles::fromFont(&FreeSans9pt7b, 12 /* <- Line height */);
Button::Styles *style3 = new Button::Styles(
  new Button::Style(0x0000, 0xFFFF, 0xFFFF) // In order: Background color, text color, border color. Setting the background color to the page's background color will improve performance.
);
Button::Styles *style4 = new Button::Styles(
  new Button::Style(0xFFFF, 0x0000, 0xFFFF, 15) // 4th parameter is border radius
);

Button::Styles *style5 = new Button::Styles(
  new Button::Style(0x4228, 0xFFFF, 0x4228, 8, &FreeSans9pt7b, 12, 1), // Normal style
  new Button::Style(0x5AEB, 0xFFFF, 0x5AEB, 8, &FreeSans9pt7b, 12, 1), // Hover (not needed for touch screens, can be replaced with NULL)
  new Button::Style(0x7BCF, 0xFFFF, 0x7BCF, 8, &FreeSans9pt7b, 12, 1) // Active/down
); 
// ^ Note: Having a different background color for different states is not recommended if the button is large or the Arduino board is not fast.

Label::Style *labelStyle = new Label::Style(0xFFFF);
Label *counterLabel;
int counter = 0;

void setup() {
  // Parameters in order: X, Y, width, height, label, style, click handler, [click behavior]
  mainPage.addChild(new Button(10, 10, 220, 50, "Default style", style1, NULL));
  mainPage.addChild(new Button(10, 70, 220, 50, "With proper font", style2, NULL));
  mainPage.addChild(new Button(10, 130, 220, 50, "No background", style3, NULL));
  mainPage.addChild(new Button(70, 190, 100, 30, "Smol", style4, smolOnClick));

  // Click behavior demo
  // "up" means the click is triggered after the pointer is released.
  // "down" means the click is triggered as soon as the pointer is pressed.
  // "down" is more responsive but "up" can prevent accidental misclicks.
  mainPage.addChild(new Button(10, 230, 105, 40, "Click me", style5, increaseCounter, Button::ClickBehavior::up));
  mainPage.addChild(new Button(120, 230, 105, 40, "Click me", style5, increaseCounter, Button::ClickBehavior::down));
  mainPage.addChild(counterLabel = new Label("0 Clicks", labelStyle, 280, Label::TextAlign::middle, 0, true));
  app.init(mainPage);
}

void loop() {
  app.update();
}

void smolOnClick(Button *sender) {
  sender->setStyle(style3->normal); // Remove background
}

void increaseCounter(Button *sender) {
  char text[30];
  itoa(++counter, text, 10);
  strcat(text, " Clicks");
  counterLabel->setText(text);
}
