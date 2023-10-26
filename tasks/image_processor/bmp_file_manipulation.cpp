#include "image_processor.h"

BMP::BMP(int32_t width, int32_t height) {
    if (std::min(width, height) <= 0) {
        throw std::runtime_error("Incorrect parameters.");
    }
    bmp_info_header.width = width;
    bmp_info_header.height = height;
    bmp_info_header.size = sizeof(BMPInfoHeader);
    bmp_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    cur_stride = width * 3; //3 - const, number of bytes in 24 bits
    data.resize(cur_stride * height);
    uint32_t new_stride = align_(static_cast<uint32_t>(4));
    bmp_file_header.file_size = bmp_file_header.offset_data + static_cast<uint32_t>(data.size()) + bmp_info_header.height * (new_stride - cur_stride);
}

void BMP::write_headers(std::ofstream& of) {
    of.write((const char*)(&bmp_file_header), sizeof(bmp_file_header));
    of.write((const char*)(&bmp_info_header), sizeof(bmp_info_header));
}

void BMP::write_all(std::ofstream& of) {
    write_headers(of);
    of.write((const char*)data.data(), data.size());
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
            //TODO - handle negative height

            if (bmp_info_header.height > 0) {

                data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

                if (bmp_info_header.width % 4 == 0) {
                    inp.read((char*)data.data(), data.size());
                    bmp_file_header.file_size += static_cast<uint32_t>(data.size());
                }
                else {
                    cur_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
                    uint32_t new_stride = align_(4);
                    std::vector<uint8_t> padding_row(new_stride - cur_stride);

                    for (int y = 0; y < bmp_info_header.height; ++y) {
                        inp.read((char*)(data.data() + cur_stride * y), cur_stride);
                        inp.read((char*)padding_row.data(), padding_row.size());
                    }
                    bmp_file_header.file_size += static_cast<uint32_t>(data.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
                }
            }
        }
        else {
            throw std::runtime_error("Unable to open the input image file.");
        }
}
