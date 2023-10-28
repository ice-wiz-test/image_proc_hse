#pragma once
#include "matrix_filters.h"

class Controller {
public:
    NegativeFilter neg = NegativeFilter();
    SharpeningFilter sharp = SharpeningFilter();
    GrayFilter gr = GrayFilter();
    EdgeDetectionFilter edg = EdgeDetectionFilter(static_cast<double>(0));
    std::vector<std::string> use_sequential;
    Controller();
    void MakeAllAdjustments(BMP& image);
    void AddString(std::string s1);
};