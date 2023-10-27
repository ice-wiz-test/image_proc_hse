#include "image_processor.h"
#include "pixel.h"

void BMP::crop(int32_t new_height, int32_t new_width) {
    if (std::min(new_height, new_width) <= static_cast<int32_t>(0)) {
        throw std::runtime_error("Incorrect cropping parameters!");
    }
    int32_t resulting_height = std::min(bmp_info_header.height, new_height);
    int32_t resulting_width = std::min(bmp_info_header.width, new_width);
    std::vector<std::vector<Pixel>> new_data;
    new_data.resize(resulting_height);
    for (int32_t height_iter = 0; height_iter < resulting_height; ++height_iter) {
        new_data[height_iter].resize(resulting_width);
    }
    for (int32_t height_iter = bmp_info_header.height - resulting_height; height_iter < bmp_info_header.height; ++height_iter) {
        for(int32_t row_iter = 0; row_iter < resulting_width; ++row_iter) {
            new_data[height_iter - bmp_info_header.height + resulting_height][row_iter].blue = data[height_iter][row_iter].blue;
            new_data[height_iter - bmp_info_header.height + resulting_height][row_iter].green = data[height_iter][row_iter].green;
            new_data[height_iter - bmp_info_header.height + resulting_height][row_iter].red = data[height_iter][row_iter].red;
        }
    }
    BMP copyBMP = BMP(resulting_width, resulting_height);
    swap(data, new_data);
    bmp_file_header = copyBMP.bmp_file_header;
    bmp_info_header = copyBMP.bmp_info_header;
    bmp_color_header = copyBMP.bmp_color_header;
    cur_stride = 3 * resulting_width;
}