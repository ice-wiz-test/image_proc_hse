#pragma once
#include "image_processor.h"
#include <string>
#include <cmath>

const std::vector<std::vector<double>> sharp_matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const std::vector<std::vector<double>> neg_matrix = {{255, -1, 0, 0}, {255, 0, -1, 0}, {255, 0, 0, -1}};
const std::vector<std::vector<double>> gray_matrix = {
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)}, 
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)}, 
    {0, static_cast<double>(0.299), static_cast<double>(0.587), static_cast<double>(0.114)}};
const std::vector<std::vector<double>> edge_matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

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

class MatrixFilter : public AbstractFilter {
public:
    std::vector<std::vector<double>> matrix;
    MatrixFilter(std::vector<std::vector<double>> corresponding_matrix)
        : AbstractFilter("Matrix filter.") {
        matrix = corresponding_matrix;
    }

    MatrixFilter(std::vector<std::vector<double>> corr_matrix, std::string name_of_filter) : AbstractFilter(name_of_filter) {
        matrix = corr_matrix;
    } 

    void Process(BMP& image);

    void Process(BMP& image, double threshold);
};

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter() : MatrixFilter(sharp_matrix) {
    }

};

class LinearFilter : public AbstractFilter {
public:
    std::vector<std::vector<double>> linear_filters;
    LinearFilter(std::vector<std::vector<double>> lin_matrix) : AbstractFilter("Linear filter") {
        linear_filters = lin_matrix;
    }

    LinearFilter(std::vector<std::vector<double>> lin_matrix, std::string filter_name) : AbstractFilter(filter_name) {
        linear_filters = lin_matrix;
    }

    void Process(BMP& image);
};

class NegativeFilter : public LinearFilter {
public:
    NegativeFilter() : LinearFilter(neg_matrix) {
    }
};

class GrayFilter : public LinearFilter {
public:
    GrayFilter() : LinearFilter(gray_matrix) {
    }
};

class EdgeDetectionFilter : public GrayFilter, public MatrixFilter{
public:
    double threshold;
    EdgeDetectionFilter(double Threshold) : GrayFilter(), MatrixFilter(edge_matrix) {
        threshold = Threshold;
    }

    void Process(BMP& image) {
        GrayFilter::Process(image);
        MatrixFilter::Process(image, threshold);
    }
};