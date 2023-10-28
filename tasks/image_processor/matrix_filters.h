#pragma once
#include "image_processor.h"
#include <string>
#include <cmath>

class AbstractFilter {
public:
    std::string filter_name;

    AbstractFilter(std::string s1) {
        filter_name = s1;
    };

    AbstractFilter() : AbstractFilter("Default filter."){};

    virtual void Process(BMP& image);

    const std::string get_filter_name() {
        return filter_name;
    };
};

class MatrixFilter : public AbstractFilter{
public:
    std::vector<std::vector<double>> matrix;
    MatrixFilter(std::vector<std::vector<double>> corresponding_matrix) : AbstractFilter("Matrix filter.") {
        matrix = corresponding_matrix;
    }

    void Process(BMP& image);
};

