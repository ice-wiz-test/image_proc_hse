#include "controller.h"

const size_t MAXSIZE = 1000;
const size_t MAXSTRSIZE = 5;

Controller::Controller() {
    neg = NegativeFilter();
    gr = GrayFilter();
    sharp = SharpeningFilter();
}

void Controller::AddString(std::string s1) {
    use_sequential.push_back(s1);
}

void Controller::MakeAllAdjustments(BMP& image) {
    size_t current_string_index = 0;
    std::cerr << " Beginning\n";
    if (use_sequential.size() > MAXSIZE) {
        throw std::runtime_error("We cannot handle so many filters");
    }
    while (current_string_index < use_sequential.size()) {
        if (use_sequential[current_string_index] == "-gs") {
            gr.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential[current_string_index] == "-neg") {
            neg.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential[current_string_index] == "-sharp") {
            sharp.Process(image);
            current_string_index++;
            continue;
        }
        if (use_sequential[current_string_index].substr(0, MAXSTRSIZE) == "-edge") {
            double d = -1;
            std::string left_to_do = use_sequential[current_string_index].substr(MAXSTRSIZE);
            try {
                d = stod(left_to_do);
            } catch (const std::exception& e) {
                current_string_index++;
                continue;
            }
            edg = EdgeDetectionFilter(d);
            edg.Process(image);
            current_string_index++;
            continue;
        }
    }
    std::cerr << " Ending\n";
}