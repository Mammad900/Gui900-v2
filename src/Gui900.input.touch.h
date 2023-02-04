#ifndef __GUI900_INPUT_TOUCH_H__
#define __GUI900_INPUT_TOUCH_H__

#include <Arduino.h>
#include <TouchScreen.h>
#include "Gui900.h"

namespace Gui900 {
    /// @brief Uses touch screen input via the Adafruit TouchScreen library.
    class TouchInput : public Input {
        private:
            int minPressure, maxPressure;
            int XP, XM, YP, YM;
            int tsLeft, tsRight, tsTop, tsBottom;
            int pixelX, pixelY, pixelZ;
            unsigned long lastTouch;
            bool isPressed;
            TouchScreen *screen;
            bool Touch_getXY();

        public:
            /// @brief Creates a new instance of the TouchInput class. You can run the Touchscreen_Calibr_native example from the MCUFRIEND_kbv to get the calibration values.
            TouchInput(int XP, int XM, int YP, int YM, int tsLeft, int tsRight, int tsTop, int tsBottom, int minPressure, int maxPressure);

            void update();
    };
}

#endif /* __GUI900_INPUT_TOUCH_H__ */
