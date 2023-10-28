#include "image_processor.h"
#include "pixel.h"

BMP::BMP(int32_t width, int32_t height) {
    if (height <= 0 || width <= 0) {
        throw std::runtime_error("Incorrect parameters.");
    }
    bmp_info_header.width = width;
    bmp_info_header.height = height;
    bmp_info_header.size = sizeof(BMPInfoHeader);
    bmp_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    cur_stride = width * 3;  // 3 - const, number of bytes in 24 bits;
    data.resize(height);
    for (int32_t height_iter = 0; height_iter < height; ++height_iter) {
        data[height_iter].resize(width);
    }
    uint32_t new_stride = Align(static_cast<uint32_t>(4));
    bmp_file_header.file_size = bmp_file_header.offset_data +
                                static_cast<uint32_t>(height) * static_cast<uint32_t>(width) * 3 +
                                bmp_info_header.height * (new_stride - cur_stride);
}

void BMP::WriteHeaders(std::ofstream& of) {
    of.write(reinterpret_cast<const char*>(&bmp_file_header), sizeof(bmp_file_header));
    of.write(reinterpret_cast<const char*>(&bmp_info_header), sizeof(bmp_info_header));
}

void BMP::WriteAll(std::ofstream& of) {
    WriteHeaders(of);
    uint32_t new_stride = Align(static_cast<uint32_t>(4));
    for (int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
        for (int32_t x = 0; x < bmp_info_header.width; ++x) {
            std::vector<uint8_t> wrapper_around_struct = {data[row_index][x].blue, data[row_index][x].green,
                                                          data[row_index][x].red};
            of.write(reinterpret_cast<const char*>(wrapper_around_struct.data()),
                     static_cast<std::streamsize>(wrapper_around_struct.size()));
        }
        for (uint32_t padding = 0; padding < new_stride - cur_stride; ++padding) {
            std::vector<uint8_t> a = {0};
            of.write(reinterpret_cast<const char*>(a.data()), static_cast<std::streamsize>(a.size()));
        }
    }
}

void BMP::Read(const char* fname) {
    std::ifstream inp{fname, std::ios_base::binary};
    if (inp) {
        inp.read(reinterpret_cast<char*>(&bmp_file_header), sizeof(bmp_file_header));
        if (bmp_file_header.file_type != FILETYPE) {
            throw std::runtime_error("Please use the correct format");
        }
        inp.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
        inp.seekg(bmp_file_header.offset_data, inp.beg);
        bmp_info_header.size = sizeof(BMPInfoHeader);
        bmp_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        bmp_file_header.file_size = bmp_file_header.offset_data;
        if (bmp_info_header.height > 0) {
            data.resize(bmp_info_header.height);
            for (int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
                data[row_index].resize(bmp_info_header.width);
            }
            if (bmp_info_header.width % 4 == 0) {
                for (int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
                    for (int32_t second_index = 0; second_index < bmp_info_header.width; ++second_index) {
                        std::vector<uint8_t> next_color(3);
                        inp.read(reinterpret_cast<char*>(next_color.data()),
                                 static_cast<std::streamsize>(next_color.size()));
                        data[row_index][second_index] = Pixel(next_color[0], next_color[1], next_color[2]);
                    }
                }
                bmp_file_header.file_size += static_cast<uint32_t>(bmp_info_header.height * bmp_info_header.width * 3);
            } else {
                cur_stride = bmp_info_header.width * 3;
                uint32_t new_stride = Align(4);
                std::vector<uint8_t> padding_row(new_stride - cur_stride);
                std::vector<uint8_t> cur_bytes(cur_stride);
                for (int32_t y = 0; y < bmp_info_header.height; ++y) {
                    inp.read(reinterpret_cast<char*>(cur_bytes.data()), cur_stride);
                    inp.read(reinterpret_cast<char*>(padding_row.data()),
                             static_cast<std::streamsize>(padding_row.size()));
                    for (int32_t x = 0; x < bmp_info_header.width; ++x) {
                        data[y][x] = Pixel(cur_bytes[x * 3], cur_bytes[x * 3 + 1], cur_bytes[x * 3 + 2]);
                    }
                }
                bmp_file_header.file_size += static_cast<uint32_t>(data.size()) +
                                             bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
            }
        } else {
            std::cout << "This program only works with positive heights\n";
            throw std::runtime_error("This program only works with positive heights.");
        }
    } else {
        std::cout << " Unable to open the input image file\n";
        throw std::runtime_error("Unable to open the input image file.");
    }
}

BMP::BMP(const char* fname) {
    Read(fname);
}

void BMP::Write(const char* fname) {
    std::ofstream of{fname, std::ios_base::binary};
    if (of) {
        if (bmp_info_header.bit_count == BITCOUNT) {
            WriteAll(of);
        } else {
            throw std::runtime_error("This program only works with 24-bit BMP image at the moment");
        }
    } else {
        throw std::runtime_error("Unable to open the output image file.");
    }
}