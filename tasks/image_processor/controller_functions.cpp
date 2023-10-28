#include "controller.h"

Controller::Controller() {
    neg = NegativeFilter();
    gr = GrayFilter();
    sharp = SharpeningFilter();
}

void Controller::add_string(std::string s1) {
    use_sequential.push_back(s1);
}

void Controller::make_all_adjustments(BMP& image) {
    size_t current_string_index = 0;
    if (use_sequential.size() > static_cast<size_t>(1000)) {
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
        if (use_sequential[current_string_index].substr(0, 5) == "-edge") {
            double d = -1;
            std::string left_to_do = use_sequential[current_string_index].substr(5);
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
}