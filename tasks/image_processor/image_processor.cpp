#include "controller.h"
#include "image_processor.h"
#include "matrix_filters.h"

const int MAXFILTER = 100;

int main(int argc, char** argv) {
    run_tests();
    if (argc < 3 || argc > MAXFILTER) {
        std::cerr << "We do not support your request at the moment" << std::endl;
        return 0;
    }
    std::string file_name = argv[1];
    BMP write_bmp;
    try {
        write_bmp = BMP(file_name.c_str());
    } catch (std::exception& e) {
        std::cerr << "Try again\n" << std::endl;
        return 0;
    }
    std::string write_to_name = argv[2];
    Controller current_controller = Controller();
    for (int j = 3; j < argc; ++j) {
        std::string current_argument = argv[j];
        current_controller.AddString(current_argument);
    }
    current_controller.MakeAllAdjustments(write_bmp);
    try {
        write_bmp.Write(write_to_name.c_str());
    } catch (std::exception& e) {
        std::cerr << "Try again\n" << std::endl;
        return 0;
    }
}
