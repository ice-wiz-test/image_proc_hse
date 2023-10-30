#pragma once
#include "matrix_filters.h"

class Controller {
private:
    NegativeFilter neg_;
    SharpeningFilter sharp_;
    GrayFilter gr_;
    EdgeDetectionFilter edg_ =
        EdgeDetectionFilter(static_cast<double>(0));  // so that there is no non-explicit operators
    GaussianFilter gg_ = GaussianFilter(static_cast<double>(0));
    PixellateFilter pf_ = PixellateFilter(0);
    std::vector<std::string> use_sequential_;

public:
    Controller();
    void MakeAllAdjustments(BMP& image);
    void AddString(std::string s1);
};
