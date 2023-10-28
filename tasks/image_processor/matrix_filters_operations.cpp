#include "matrix_filters.h"

const double minimum_value = 0;
const double maximum_value = 255;

double norm_double(double t1) {
    return std::max(minimum_value, std::min(maximum_value, t1));
}

double try_double(double t1, double threshold) {
    if (t1 > threshold) {
        return maximum_value;
    } else {
        return minimum_value;
    }
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
        for (int32_t other_index = 0; other_index < image.bmp_info_header.width; ++other_index) {
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
            new_data[row_index][other_index] =
                Pixel(get_pixel_from_double(resulting_blue), get_pixel_from_double(resulting_green),
                      get_pixel_from_double(resulting_red));
        }
    }
    image.data = new_data;
}

void LinearFilter::Process(BMP& image) {
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        for (int32_t other_index = 0; other_index < image.bmp_info_header.width; ++other_index) {
            Pixel* cur_pixel = image.at(row_index, other_index);
            double resulting_blue = linear_filters[0][0] + linear_filters[0][1] * static_cast<double>(cur_pixel->blue) +
                                    linear_filters[0][2] * static_cast<double>(cur_pixel->green) +
                                    linear_filters[0][3] * static_cast<double>(cur_pixel->red);
            double resulting_green = linear_filters[1][0] +
                                     linear_filters[1][1] * static_cast<double>(cur_pixel->blue) +
                                     linear_filters[1][2] * static_cast<double>(cur_pixel->green) +
                                     linear_filters[1][3] * static_cast<double>(cur_pixel->red);
            double resulting_red = linear_filters[2][0] + linear_filters[2][1] * static_cast<double>(cur_pixel->blue) +
                                   linear_filters[2][2] * static_cast<double>(cur_pixel->green) +
                                   linear_filters[2][3] * static_cast<double>(cur_pixel->red);
            resulting_blue = norm_double(resulting_blue);
            resulting_green = norm_double(resulting_green);
            resulting_red = norm_double(resulting_red);
            cur_pixel->blue = resulting_blue;
            cur_pixel->green = resulting_green;
            cur_pixel->red = resulting_red;
        }
    }
}

void MatrixFilter::Process(BMP& image, double threshold) {
    std::vector<std::vector<Pixel>> new_data;
    new_data.resize(image.bmp_info_header.height);
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        new_data[row_index].resize(image.bmp_info_header.width);
    }
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        for (int32_t other_index = 0; other_index < image.bmp_info_header.width; ++other_index) {
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
            resulting_blue = try_double(resulting_blue, threshold);
            resulting_green = try_double(resulting_green, threshold);
            resulting_red = try_double(resulting_red, threshold);
            new_data[row_index][other_index] = 
                Pixel(get_pixel_from_double(resulting_blue), get_pixel_from_double(resulting_green),
                    get_pixel_from_double(resulting_red));
        }
    }
    image.data = new_data;
}