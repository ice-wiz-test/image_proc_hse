#include "image_processor.h"

int main(int argc, char** argv) {
    if (argc == 0) {
        std::cout << "Hello! This program can work with BMP images!\n";
        return 0;
    }
    std::cout << " about to open\n";
    BMP testing_bmp = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test_script/data/flag.bmp");
    testing_bmp.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/ahahah.bmp");
}
