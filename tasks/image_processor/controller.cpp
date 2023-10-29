#include "controller.h"

const size_t MAXSIZE = 1000;
const size_t MAXSTRSIZE = 5;

Controller::Controller() {
    neg_ = NegativeFilter();
    gr_ = GrayFilter();
    sharp_ = SharpeningFilter();
}

void Controller::AddString(std::string s1) {
    use_sequential_.push_back(s1);
}

void Controller::MakeAllAdjustments(BMP& image) {
    size_t current_string_index = 0;
    std::cerr << " Beginning\n";
    if (use_sequential_.size() > MAXSIZE) {
        throw std::runtime_error("We cannot handle so many filters");
    }
    while (current_string_index < use_sequential_.size()) {
        if (use_sequential_[current_string_index] == "-gs") {
            gr_.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential_[current_string_index] == "-neg") {
            neg_.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential_[current_string_index] == "-sharp") {
            sharp_.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential_[current_string_index].substr(0, MAXSTRSIZE) == "-edge") {
            std::cerr << " DOING EDGE \n";
            double d = -1;
            std::string left_to_do = use_sequential_[current_string_index + 1];
            try {
                d = stod(left_to_do);
                std::cerr << d << " CUR \n";
            } catch (const std::exception& e) {
                current_string_index += 2;
                continue;
            }
            edg_ = EdgeDetectionFilter(d);
            edg_.Process(image);
            current_string_index += 2;
            continue;
        }
        if (use_sequential_[current_string_index].substr(0, MAXSTRSIZE) == "-blur") {
            std::cerr << " DOING BLUR \n";
            double d = -1;
            std::string left_to_do = use_sequential_[current_string_index + 1];
            try {
                d = stod(left_to_do);
                std::cerr << d << " CUR \n";
            } catch (const std::exception& e) {
                current_string_index += 2;
                continue;
            }
            gg_ = GaussianFilter(d);
            gg_.Process(image);
            current_string_index += 2;
            continue;
        }
        current_string_index++;
    }
    std::cerr << " Ending\n";
}