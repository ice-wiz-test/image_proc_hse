#include "image_processor.h"
#include "matrix_filters.h"
#include "controller.h"

int main(int argc, char** argv) {
    if (argc < 3 || argc > 100) {
        std::cerr << "We do not support your request at the moment" << std::endl;
        return 0;
    }
    std::string file_name = argv[1];
    std::cerr << file_name << " name !" << std::endl;
    BMP write_BMP;
    try {
        write_BMP = BMP(file_name.c_str());
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
    current_controller.MakeAllAdjustments(write_BMP);
    try {
        write_BMP.Write(write_to_name.c_str());
    } catch (std::exception& e) {
        std::cerr << "Try again\n" << std::endl;
        return 0;
    }
}
