#include "image_processor.h"

int main(int argc, char** argv) {
    if (argc == 0) {
        std::cout << "Hello! This program can work with BMP images!\n";
        return 0;
    }
    BMP testing_bmp = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test_script/data/lenna_crop.bmp");
    std::cout << testing_bmp.bmp_info_header.width << " " << testing_bmp.bmp_info_header.height << "\n";
    testing_bmp.crop(1000, 999);
    testing_bmp.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/new_bmp.bmp");
    BMP testing_bmp_2 = BMP(201, 201);
}
