#pragma once
#include "matrix_filters.h"

class Controller {
private:
    NegativeFilter neg;
    SharpeningFilter sharp;
    GrayFilter gr;
    EdgeDetectionFilter edg =
        EdgeDetectionFilter(static_cast<double>(0));  // so that there is no non-explicit operators
    GaussianFilter gg = GaussianFilter(static_cast<double>(0));
    std::vector<std::string> use_sequential;

public:
    Controller();
    void MakeAllAdjustments(BMP& image);
    void AddString(std::string s1);
};
