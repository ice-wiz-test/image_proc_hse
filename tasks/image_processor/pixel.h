#pragma once
#include <cstdint>

struct Pixel {
    uint8_t red = 0;
    uint8_t blue = 0;
    uint8_t green = 0;
    Pixel(uint8_t B, uint8_t G, uint8_t R) {
        red = R;
        blue = B;
        green = G;
    };
    Pixel() : Pixel(static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0)){};
};