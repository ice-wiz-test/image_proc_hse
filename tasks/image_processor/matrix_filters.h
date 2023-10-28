#pragma once
#include "image_processor.h"
#include <string>
#include <cmath>

const std::vector<std::vector<double>> SHARP_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const std::vector<std::vector<double>> NEG_MATRIX = {{255, -1, 0, 0}, {255, 0, -1, 0}, {255, 0, 0, -1}};
const std::vector<std::vector<double>> GRAY_MATRIX = {
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)},
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)},
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)}};
const std::vector<std::vector<double>> EDGE_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

class AbstractFilter {
public:
    std::string filter_name;

    explicit AbstractFilter(std::string s1) {
        filter_name = s1;
    };

    AbstractFilter() : AbstractFilter("Default filter."){};

    virtual void Process(BMP& image);

    std::string GetFilterName() {
        return filter_name;
    };
};

class MatrixFilter : public AbstractFilter {
public:
    std::vector<std::vector<double>> matrix;
    explicit MatrixFilter(std::vector<std::vector<double>> corresponding_matrix) : AbstractFilter("Matrix filter.") {
        matrix = corresponding_matrix;
    }

    explicit MatrixFilter(std::vector<std::vector<double>> corr_matrix, std::string name_of_filter)
        : AbstractFilter(name_of_filter) {
        matrix = corr_matrix;
    }

    void Process(BMP& image);

    void Process(BMP& image, double threshold);
};

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter() : MatrixFilter(SHARP_MATRIX) {
    }
};

class LinearFilter : public AbstractFilter {
public:
    std::vector<std::vector<double>> linear_filters;
    explicit LinearFilter(std::vector<std::vector<double>> lin_matrix) : AbstractFilter("Linear filter") {
        linear_filters = lin_matrix;
    }

    explicit LinearFilter(std::vector<std::vector<double>> lin_matrix, std::string filter_name)
        : AbstractFilter(filter_name) {
        linear_filters = lin_matrix;
    }

    void Process(BMP& image);
};

class NegativeFilter : public LinearFilter {
public:
    NegativeFilter() : LinearFilter(NEG_MATRIX) {
    }
};

class GrayFilter : public LinearFilter {
public:
    GrayFilter() : LinearFilter(GRAY_MATRIX) {
    }
};

class EdgeDetectionFilter : public GrayFilter, public MatrixFilter {
public:
    double threshold;
    EdgeDetectionFilter(double Threshold) : GrayFilter(), MatrixFilter(EDGE_MATRIX) {
        threshold = Threshold;
    }

    void Process(BMP& image) {
        GrayFilter::Process(image);
        MatrixFilter::Process(image, threshold);
    }
};