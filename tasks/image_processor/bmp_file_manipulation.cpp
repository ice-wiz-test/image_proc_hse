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
    cur_stride = width * 3; //3 - const, number of bytes in 24 bits; 
    data.resize(height);
    for(int32_t height_iter = 0; height_iter < height; ++height_iter) {
        data[height_iter].resize(width);
    }
    uint32_t new_stride = align_(static_cast<uint32_t>(4));
    bmp_file_header.file_size = bmp_file_header.offset_data + static_cast<uint32_t>(height) * static_cast<uint32_t>(width) + bmp_info_header.height * (new_stride - cur_stride);
}

void BMP::write_headers(std::ofstream& of) {
    of.write((const char*)(&bmp_file_header), sizeof(bmp_file_header));
    of.write((const char*)(&bmp_info_header), sizeof(bmp_info_header));
}

void BMP::write_all(std::ofstream& of) {
    write_headers(of);
    int new_stride = align_(static_cast<uint32_t>(4));
    for(int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
        of.write((const char*)data[row_index].data(), data[row_index].size());
        for(uint32_t padding = 0; padding < new_stride - cur_stride; ++padding) {
            of.write("0", 1);
        }
    }
}

void BMP::read(const char* fname) {
    std::ifstream inp{ fname, std::ios_base::binary };
        if (inp) {
            inp.read((char*)(&bmp_file_header), sizeof(bmp_file_header));
            if(bmp_file_header.file_type != 0x4D42) {
                throw std::runtime_error("Please use the correct format");
            }
            inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));
            inp.seekg(bmp_file_header.offset_data, inp.beg);
            bmp_info_header.size = sizeof(BMPInfoHeader);
            bmp_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
            
            bmp_file_header.file_size = bmp_file_header.offset_data;

            if (bmp_info_header.height > 0) {
                data.resize(bmp_info_header.height);
                for(int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
                    data[row_index].resize(bmp_info_header.width);
                }

                if (bmp_info_header.width % 4 == 0) {
                    for (int32_t row_index = 0; row_index < bmp_info_header.height; ++row_index) {
                        for (int32_t second_index = 0; second_index < bmp_info_header.width; ++second_index) {
                            std::vector<uint8_t> next_color(3);
                            inp.read((char*)next_color.data(), data.size());
                            data[row_index][second_index] = Pixel(next_color[0], next_color[1], next_color[2]);
                        }
                    }
                    bmp_file_header.file_size += static_cast<uint32_t>(bmp_info_header.height * bmp_info_header.width);
                }
                else {
                    cur_stride = bmp_info_header.width * 3;
                    uint32_t new_stride = align_(4);
                    std::vector<uint8_t> padding_row(new_stride - cur_stride);
                    std::vector<uint8_t> cur_bytes(cur_stride);
                    for (int32_t y = 0; y < bmp_info_header.height; ++y) {
                        //inp.read((char*)(data.data() + cur_stride * y), cur_stride);
                        //inp.read((char*)padding_row.data(), padding_row.size());
                        inp.read((char*)(cur_bytes.data()), cur_stride);
                        inp.read((char*)padding_row.data(), padding_row.size());
                        for(int32_t x = 0; x < bmp_info_header.width; ++x) {
                            data[y][x] = Pixel(cur_bytes[x * 3], cur_bytes[x * 3 + 1], cur_bytes[x * 3 + 2]);
                        }
                    }
                    bmp_file_header.file_size += static_cast<uint32_t>(data.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
                }
            } else {
                throw std::runtime_error("This program only works with positive heights.");
            }
        }
        else {
            throw std::runtime_error("Unable to open the input image file.");
        }
}

BMP::BMP(const char* fname) {
    read(fname);
}

void BMP::write(const char *fname) {
    std::ofstream of{ fname, std::ios_base::binary };
        if (of) {
            if (bmp_info_header.bit_count == 24) {
                if (bmp_info_header.width % 4 == 0) {
                    write_headers(of);
                }
                else {
                    uint32_t new_stride = align_(4);
                    std::vector<uint8_t> padding_row(new_stride - cur_stride);

                    write_headers(of);

                    for (int y = 0; y < bmp_info_header.height; ++y) {
                        for(int x = 0; x < bmp_info_header.width; ++x) {
                            std::vector<uint8_t> current_write = {data[y][x].blue, data[y][x].green, data[y][x].red};
                            of.write((const char*)(current_write.data()), current_write.size());
                        }
                        of.write((const char*)padding_row.data(), padding_row.size());
                    }
                }
            } else {
                throw std::runtime_error("This program only works with 24-bit BMP image at the moment");    
            }
        }
        else {
            throw std::runtime_error("Unable to open the output image file.");
        }
}