#pragma once
#include <cstdint>

struct Pixel {
    uint8_t red = 0;
    uint8_t blue = 0;
    uint8_t green = 0;
    Pixel(uint8_t b, uint8_t g, uint8_t r) {
        red = r;
        blue = b;
        green = g;
    };
    Pixel() : Pixel(static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0)){};
};