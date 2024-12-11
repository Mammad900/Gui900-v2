#include <Gui900.h>
#include <Gui900.display.mcufriend_kbv.h>
#include <Gui900.page.h>
#include <Gui900.element.image.h>
#include <Gui900.image.h>
#include <Gui900.image.source.progmem.h>
#include <Gui900.image.format.raw565.h>
#include <Gui900.util.h>

// Our image is in here
#include "bitmap.h"

using namespace Gui900;
using namespace Gui900::Elements;

Display_MCUFRIEND_kbv tft;
Input input;
App app(Orientation::landscape, tft, input);

Page mainPage(&app, Util::color565(0, 0, 0));
Image::Sources::Progmem source = Image::Sources::Progmem(marilyn_64x64); // Use the bitmap which is a PROGMEM buffer
Image::Formats::Raw565 format = Image::Formats::Raw565(source, 64, 64); // Parse it as a 64*64 image in RGB565 (16 bit) format

void setup() {
  // put your setup code here, to run once:
  mainPage.addChild(new Elements::Image(50, 50, format));
  app.init(mainPage);
}

void loop() {
  // put your main code here, to run repeatedly:
  app.update();
}
