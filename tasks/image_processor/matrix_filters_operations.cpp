#include "matrix_filters.h"

const double minimum_value = 0;
const double maximum_value = 255;

double norm_double(double t1) {
    return std::max(minimum_value, std::min(maximum_value, t1));
}

void AbstractFilter::Process(BMP& image) {
    return;
}

uint8_t get_pixel_from_double(double t1) {
    long long get_rounded = std::llround(t1);
    return static_cast<uint8_t>(get_rounded);
}

void MatrixFilter::Process(BMP& image) {
    std::vector<std::vector<Pixel>> new_data;
    new_data.resize(image.bmp_info_header.height);
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        new_data[row_index].resize(image.bmp_info_header.width);
    }
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        for(int32_t other_index = 0; other_index < image.bmp_info_header.width; ++other_index) {
            double resulting_blue = 0;
            double resulting_green = 0;
            double resulting_red = 0;
            for (int32_t x_coord = 0; x_coord < 3; ++x_coord) {
                for (int32_t y_coord = 0; y_coord < 3; ++y_coord) {
                    Pixel* pixel_reference = image.at(row_index - 1 + x_coord, other_index - 1 + y_coord);
                    resulting_blue += static_cast<double>(pixel_reference->blue) * matrix[x_coord][y_coord];
                    resulting_green += static_cast<double>(pixel_reference->green) * matrix[x_coord][y_coord];
                    resulting_red += static_cast<double>(pixel_reference->red) * matrix[x_coord][y_coord];
                }
            }
            resulting_blue = norm_double(resulting_blue);
            resulting_green = norm_double(resulting_green);
            resulting_red = norm_double(resulting_red);
            new_data[row_index][other_index] = Pixel(get_pixel_from_double(resulting_blue), get_pixel_from_double(resulting_green), get_pixel_from_double(resulting_red));
        }
    }
    image.data = new_data;
}