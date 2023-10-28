#pragma once
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "pixel.h"

const uint16_t FILETYPE = 0x4D42;
const uint16_t BITCOUNT = 24;
const uint32_t REDMASK = 0x00ff0000;
const uint32_t BLUEMASK = 0x000000ff;
const uint32_t GREENMASK = 0x0000ff00;
const uint32_t ALPHAMASK = 0xff000000;
const uint32_t CLST = 0x73524742;
const size_t UNUSED_SIZE = 16;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type = FILETYPE;
    uint32_t file_size = 0;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offset_data = 0;
};

struct BMPInfoHeader {
    uint32_t size = 0;
    int32_t width = 0;
    int32_t height = 0;
    uint16_t planes = 1;
    uint16_t bit_count = BITCOUNT;  // yes, it is const; no, i don't really care
    uint32_t compression = 0;
    uint32_t size_image = 0;
    int32_t x_pixels_per_meter = 0;
    int32_t y_pixels_per_meter = 0;
    uint32_t colors_used = 0;
    uint32_t colors_important = 0;
};

struct BMPColorHeader {
    uint32_t red_mask = REDMASK;
    uint32_t green_mask = GREENMASK;
    uint32_t blue_mask = BLUEMASK;
    uint32_t alpha_mask = ALPHAMASK;
    uint32_t color_space_type = CLST;
    uint32_t unused[UNUSED_SIZE]{0};
};
#pragma pack(pop)

class BMP {
public:
    BMPFileHeader bmp_file_header;
    BMPInfoHeader bmp_info_header;
    BMPColorHeader bmp_color_header;
    std::vector<std::vector<Pixel>> data;
    uint32_t cur_stride{};

    BMP(){};

    explicit BMP(const char* file_name);

    void Read(const char* file_name);

    BMP(int32_t width, int32_t height);

    void Write(const char* file_name);

    void Crop(int32_t new_height, int32_t new_width);

    Pixel* At(int32_t x0, int32_t y0);

private:
    uint32_t Align (uint32_t align_by) const;

    void CheckCorrectColors(BMPColorHeader& current_bmp_color_header);

    void WriteAll(std::ofstream& of);

    void WriteHeaders(std::ofstream& of);
};
