#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t summary_answer = static_cast<int64_t>(0);
    std::multiset<int64_t> current_provinces;
    for (int starter_province : provinces) {
        current_provinces.insert(starter_province);
    }
    while (current_provinces.size() > static_cast<size_t>(1)) {
        int64_t first_merged_province = *current_provinces.begin();
        current_provinces.erase(current_provinces.begin());
        int64_t second_merged_province = *current_provinces.begin();
        current_provinces.erase(current_provinces.begin());
        int64_t sum = first_merged_province + second_merged_province;
        summary_answer += sum;
        current_provinces.insert(sum);
    }
    return summary_answer;
}