#include "matrix_filters.h"

const double MINIMUM_VALUE = 0;
const double MAXIMUM_VALUE = 255;
const double EPS = 0.001;

double NormDouble(double t1) {
    return std::max(MINIMUM_VALUE, std::min(MAXIMUM_VALUE, t1));
}

double TryDouble(double t1, double threshold) {
    if (t1 > threshold * MAXIMUM_VALUE) {
        return MAXIMUM_VALUE;
    } else {
        return MINIMUM_VALUE;
    }
}

void AbstractFilter::Process(BMP& image) {
}

uint8_t GetPixelFromDouble(double t1) {
    int64_t get_rounded = std::llround(t1);
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
                    Pixel* pixel_reference = image.At(row_index - 1 + x_coord, other_index - 1 + y_coord);
                    resulting_blue += static_cast<double>(pixel_reference->blue) * matrix[x_coord][y_coord];
                    resulting_green += static_cast<double>(pixel_reference->green) * matrix[x_coord][y_coord];
                    resulting_red += static_cast<double>(pixel_reference->red) * matrix[x_coord][y_coord];
                }
            }
            resulting_blue = NormDouble(resulting_blue);
            resulting_green = NormDouble(resulting_green);
            resulting_red = NormDouble(resulting_red);
            new_data[row_index][other_index] =
                Pixel(GetPixelFromDouble(resulting_blue), GetPixelFromDouble(resulting_green),
                      GetPixelFromDouble(resulting_red));
        }
    }
    image.data = new_data;
}

void LinearFilter::Process(BMP& image) {
    for (int32_t row_index = 0; row_index < image.bmp_info_header.height; ++row_index) {
        for (int32_t other_index = 0; other_index < image.bmp_info_header.width; ++other_index) {
            Pixel* cur_pixel = image.At(row_index, other_index);
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
            resulting_blue = NormDouble(resulting_blue);
            resulting_green = NormDouble(resulting_green);
            resulting_red = NormDouble(resulting_red);
            cur_pixel->blue = static_cast<uint8_t>(resulting_blue);
            cur_pixel->green = static_cast<uint8_t>(resulting_green);
            cur_pixel->red = static_cast<uint8_t>(resulting_red);
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
                    Pixel* pixel_reference = image.At(row_index - 1 + x_coord, other_index - 1 + y_coord);
                    resulting_blue += static_cast<double>(pixel_reference->blue) * matrix[x_coord][y_coord];
                    resulting_green += static_cast<double>(pixel_reference->green) * matrix[x_coord][y_coord];
                    resulting_red += static_cast<double>(pixel_reference->red) * matrix[x_coord][y_coord];
                }
            }
            resulting_blue = TryDouble(resulting_blue, threshold);
            resulting_green = TryDouble(resulting_green, threshold);
            resulting_red = TryDouble(resulting_red, threshold);
            new_data[row_index][other_index] =
                Pixel(GetPixelFromDouble(resulting_blue), GetPixelFromDouble(resulting_green),
                      GetPixelFromDouble(resulting_red));
        }
    }
    image.data = new_data;
}

void GaussianFilter::Process(BMP& image) {
    if (sigma_parameter < EPS) {
        return;
    }
    const int32_t MAX_CONSTANT = static_cast<int32_t>(3.0 * sigma_parameter);
    const double DIVIDE_BY = sqrt(2.0 * M_PI * sigma_parameter * sigma_parameter);
    const double DIVIDE_POWER = 2.0 * sigma_parameter * sigma_parameter;
    std::vector<std::vector<Pixel>> new_data;
    new_data.resize(image.bmp_info_header.height);
    for (int32_t x0 = 0; x0 < image.bmp_info_header.height; ++x0) {
        new_data[x0].resize(image.bmp_info_header.width);
    }
    for (int32_t x0 = 0; x0 < image.bmp_info_header.height; ++x0) {
        for (int32_t y0 = 0; y0 < image.bmp_info_header.width; ++y0) {
            double new_r = 0;
            double new_b = 0;
            double new_g = 0;
            for (int32_t small_x = std::max(0, x0 - MAX_CONSTANT); small_x < std::min(image.bmp_info_header.height, x0 + MAX_CONSTANT); ++small_x) {
                Pixel* pref = image.At(small_x, y0);
                double sqr = static_cast<double>((small_x - x0) * (small_x - x0));
                double mult_coeff = exp(-(sqr) / DIVIDE_POWER);
                new_r += mult_coeff * static_cast<double>(pref->red);
                new_g += mult_coeff * static_cast<double>(pref->green);
                new_b += mult_coeff * static_cast<double>(pref->blue);
            }
            new_r /= DIVIDE_BY;
            new_g /= DIVIDE_BY;
            new_b /= DIVIDE_BY;
            uint8_t new_red = GetPixelFromDouble(NormDouble(new_r));
            uint8_t new_blue = GetPixelFromDouble(NormDouble(new_b));
            uint8_t new_green = GetPixelFromDouble(NormDouble(new_g));
            new_data[x0][y0] = Pixel(new_blue, new_green, new_red);
        }
    }
    image.data = new_data;
    for (int32_t x0 = 0; x0 < image.bmp_info_header.height; ++x0) {
        for (int32_t y0 = 0; y0 < image.bmp_info_header.width; ++y0) {
            double new_r = 0;
            double new_b = 0;
            double new_g = 0;
            for (int32_t small_y = std::max(0, y0 - MAX_CONSTANT); small_y < std::min(image.bmp_info_header.width, y0 + MAX_CONSTANT); ++small_y) {
                Pixel* pref = image.At(x0, small_y);
                double sqr = static_cast<double>((small_y - y0) * (small_y - y0));
                double mult_coeff = exp(-(sqr) / DIVIDE_POWER);
                new_r += mult_coeff * static_cast<double>(pref->red);
                new_g += mult_coeff * static_cast<double>(pref->green);
                new_b += mult_coeff * static_cast<double>(pref->blue);
            }
            new_r /= DIVIDE_BY;
            new_g /= DIVIDE_BY;
            new_b /= DIVIDE_BY;
            uint8_t new_red = GetPixelFromDouble(NormDouble(new_r));
            uint8_t new_blue = GetPixelFromDouble(NormDouble(new_b));
            uint8_t new_green = GetPixelFromDouble(NormDouble(new_g));
            new_data[x0][y0] = Pixel(new_blue, new_green, new_red);
        }
    }
    image.data = new_data;
}