#include "image_processor.h"
#include "matrix_filters.h"

int main(int argc, char** argv) {
    if (argc == 0) {
        std::cout << "Hello! This program can work with BMP images!\n";
        return 0;
    }
    std::vector<std::vector<double>> sharp_matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    BMP testing_bmp = BMP("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/test_script/data/lenna.bmp");
    MatrixFilter sharp_filter = MatrixFilter(sharp_matrix);
    for(auto&x : sharp_filter.matrix) {
        for(auto&y : x) {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }
    sharp_filter.Process(testing_bmp);
    testing_bmp.write("C:/Windows/System32/2023-cpp-pmi-pilot/pmi-233-1-Prokhor-Larichev-indukvtsiane/tasks/image_processor/new_bmp.bmp");
}
