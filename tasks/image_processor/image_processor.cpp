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
    }
    catch(std::exception& e) {
        std::cerr << "Try again\n" << std::endl;
        return 0;
    }
    std::string write_to_name = argv[2];
    Controller current_controller = Controller();
    for(int j = 3; j < argc; ++j) {
        std::string current_argument = argv[j];
        current_controller.add_string(current_argument);
    }
    current_controller.make_all_adjustments(write_BMP);
    try {
        write_BMP.write(write_to_name.c_str());
    }
    catch(std::exception& e) {
        std::cerr << "Try again\n" << std::endl;
        return 0;
    }
   /*BMP write_BMP = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/lenna.bmp");
   Controller generic_controller = Controller();
   generic_controller.add_string("-gs");
   generic_controller.add_string("-neg");
   generic_controller.make_all_adjustments(write_BMP);
   write_BMP.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test2.bmp");*/
}
