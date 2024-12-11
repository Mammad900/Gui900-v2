#ifndef __GUI900_IMAGE_SOURCE_PROGMEM_H__
#define __GUI900_IMAGE_SOURCE_PROGMEM_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <avr/pgmspace.h>
#include "Gui900.h"
#include "Gui900.image.h"

namespace Gui900 {
    namespace Image {
        namespace Sources {
            class Progmem : public Source {
                public:
                    const uint8_t *buffer;
                    int pos = 0;
                    Progmem(const uint8_t *buffer) : buffer(buffer) {}
                    Progmem(const uint16_t *buffer) : buffer((uint8_t*)buffer) {}
                    void reset() {
                        pos = 0;
                    }
                    uint8_t read8() {
                        return pgm_read_byte(&buffer[pos++]);
                    }
                    uint16_t read16() {
                        uint16_t res = pgm_read_word(&buffer[pos]);
                        pos += 2;
                        return res;
                    }
                    const uint8_t *readAllProgmem() {
                        return buffer;
                    }
            };
        }
    }
}

#endif /* __GUI900_IMAGE_SOURCE_PROGMEM_H__ */
