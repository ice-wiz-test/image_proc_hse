#include "image_processor.h"
#include "matrix_filters.h"

int main(int argc, char** argv) {
    if (argc == 0) {
        std::cout << "Hello! This program can work with BMP images!\n";
        return 0;
    }
    BMP testing_bmp = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test_script/data/lenna.bmp");
    GrayFilter sharp_filter = GrayFilter();
    sharp_filter.Process(testing_bmp);
    testing_bmp.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/new_bmp.bmp");
    BMP testing_bmp_2 = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test_script/data/lenna.bmp");
    NegativeFilter neg_filter = NegativeFilter();
    neg_filter.Process(testing_bmp_2);
    testing_bmp_2.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/new_bmp_2.bmp");
}
