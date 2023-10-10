#include "search.h"

const char SMALL_A = 'a';
const char SMALL_Z = 'z';
const char BIG_A = 'A';
const char BIG_Z = 'Z';
const char STR_END = '\n';

char ConvertToLowerCase(char a) {
    if (SMALL_A <= a && a <= SMALL_Z) return a;
    if (BIG_A > a || BIG_Z < a) return a; 
    return SMALL_A + (a - BIG_A);
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    size_t current_iterator_over_docs = 0;
    std::set<std::pair<double, std::string_view>> current_answer;
    while (current_iterator_over_docs < text.size()) {
        if (text[current_iterator_over_docs] == STR_END) {
            current_iterator_over_docs++;
            continue;
        }
        size_t current_document_end = current_iterator_over_docs + 1;
        while (current_document_end < text.size() && text[current_document_end] != STR_END) {
            current_document_end++;
        }
        
    }
    return {};
}
