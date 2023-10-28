#include "image_processor.h"

uint32_t BMP::align_(uint32_t align_by) {
    uint32_t copy_stride = cur_stride;
    while (copy_stride % align_by != static_cast<uint32_t>(0)) {
        copy_stride++;
    }
    return copy_stride;
}

void BMP::check_correct_colors(BMPColorHeader& current_bmp_color_header) {
    BMPColorHeader default_header;
    if (current_bmp_color_header.alpha_mask != default_header.alpha_mask || 
        current_bmp_color_header.blue_mask != default_header.blue_mask ||
        current_bmp_color_header.red_mask != default_header.red_mask ||
        current_bmp_color_header.green_mask != default_header.green_mask) {
        throw std::runtime_error("The program expects the pixel data to be in the BGRA format");
    }
    if (default_header.color_space_type != current_bmp_color_header.color_space_type) {
        throw std::runtime_error("The program only works with sRGB values");
    }
}

Pixel* BMP::at(int32_t x0, int32_t y0) {
    int32_t resulting_x0 = x0;
    int32_t resulting_y0 = y0;
    resulting_x0 = std::max(static_cast<int32_t>(0), resulting_x0);
    resulting_x0 = std::min(resulting_x0, bmp_info_header.height - static_cast<int32_t>(1));
    resulting_y0 = std::max(static_cast<int32_t>(0), resulting_y0);
    resulting_y0 = std::min(resulting_y0, bmp_info_header.width - static_cast<int32_t>(1));
    return &data[resulting_x0][resulting_y0];
}