#include <Gui900.h>
#include <Gui900.display.mcufriend_kbv.h>
#include <Gui900.page.h>
#include <Gui900.element.image.h>
#include <Gui900.image.h>
#include <Gui900.image.source.progmem.h>
#include <Gui900.image.format.raw565.h>
#include <Gui900.image.format.solidcolor.h>
#include <Gui900.image.format.gradient.h>
#include <Gui900.image.format.monochromerle.h>
#include <Gui900.util.h>

// Our image is in here
#include "bitmap.h"

using namespace Gui900;
using namespace Gui900::Elements;

Display_MCUFRIEND_kbv tft;
Input input;
App app(Orientation::landscape, tft, input);

Page mainPage(&app, Util::color565(0, 0, 0));

// Images can have multiple formats.
// The most import one is the raw 565 format: supports full 16 bit color and is very simple to use, but no compression.
Image::Sources::Progmem source1 = Image::Sources::Progmem(marilyn_64x64); // Use the bitmap which is a PROGMEM buffer
Image::Formats::Raw565 format1 = Image::Formats::Raw565(source1, 64, 64); // Parse it as a 64*64 image in RGB565 (16 bit) format

// You can also use a solid color.
Image::Formats::SolidColor format2 = Image::Formats::SolidColor(Util::color565(0, 255, 255), 64, 64); // This image is a solid cyan

// Or a gradient. You can specify the direction and two colors.
// Only two horizontal and vertical directions are supported, and interpolation is RGB.
Image::Formats::Gradient format3 =
    Image::Formats::Gradient(
        Util::color565(255, 0, 0), // Start is red
        Util::color565(0, 255, 0), // End is green
        Image::Formats::Gradient::Direction::top_bottom,
        64, 64);

// On most UI cases, a monochrome bitmap is enough. While it may not be faster to draw, a bit packed monochrome bitmap is 16 times smaller than a 16 bit RGB one.
// To reduce the size even further I have designed my own custom compression algorithm based on Run Length Encoding.
// In this example it is 3.4x more efficient than regular bit packing.
Image::Sources::Progmem source2 = Image::Sources::Progmem(logo_64x64);
Image::Formats::MonochromeRLE format4 =
    Image::Formats::MonochromeRLE(
        source2, // Use the PROGMEM source we defined above
        Util::color565(255, 0, 0), // Red,
        Util::color565(0, 255, 0), // on green.
        64, 64);

void setup()
{
  mainPage.addChild(new Elements::Image(16, 16, format1));
  mainPage.addChild(new Elements::Image(96, 16, format2));
  mainPage.addChild(new Elements::Image(16, 96, format3));
  mainPage.addChild(new Elements::Image(96, 96, format4));
  app.init(mainPage);
}

void loop()
{
  app.update();
}
