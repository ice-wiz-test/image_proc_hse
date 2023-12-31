#include "search.h"

const char STR_END = '\n';
const double EPS = 0.000001;

bool IsAlpha(char c) {
    return isalpha(static_cast<int>(c)) != 0;
}

char MyTolower(char ch) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

std::set<std::string> DifferentWord(std::string_view text) {
    std::set<std::string> returned_set;
    size_t current_iterator = 0;
    while (current_iterator < text.size()) {
        if (!IsAlpha(text[current_iterator])) {
            current_iterator++;
            continue;
        }
        std::string current_word;
        size_t right_word_iter = current_iterator;
        while (right_word_iter < text.size() && IsAlpha(text[right_word_iter])) {
            current_word.push_back(MyTolower(text[right_word_iter]));
            right_word_iter++;
        }
        returned_set.insert(current_word);
        current_iterator = right_word_iter;
    }
    return returned_set;
}

std::map<std::string, size_t> DecompDocument(std::string_view text) {
    size_t current_iter = 0;
    std::map<std::string, size_t> stored_words;
    while (current_iter < text.size()) {
        if (!IsAlpha(text[current_iter])) {
            current_iter++;
            continue;
        }
        std::string next_word;
        size_t next_word_iter = current_iter;
        while (next_word_iter < text.size() && IsAlpha(text[next_word_iter])) {
            next_word.push_back(MyTolower(text[next_word_iter]));
            next_word_iter++;
        }
        stored_words[next_word]++;
        current_iter = next_word_iter;
    }
    return stored_words;
}

std::vector<std::string_view> DocumentDec(std::string_view text) {
    size_t current_iterator = 0;
    std::vector<std::string_view> ret_value;
    while (current_iterator < text.size()) {
        if (!IsAlpha(text[current_iterator])) {
            current_iterator++;
            continue;
        }
        size_t right_document_end = current_iterator;
        bool have_at_least_one_letter = false;
        while (right_document_end < text.size() && text[right_document_end] != STR_END) {
            if (IsAlpha(text[right_document_end])) {
                have_at_least_one_letter = true;
            }
            right_document_end++;
        }
        if (have_at_least_one_letter) {
            ret_value.push_back(text.substr(current_iterator, right_document_end - current_iterator));
        }
        current_iterator = right_document_end;
    }
    return ret_value;
}

bool Compare2(const std::pair<double, std::pair<int, std::string_view>>& s1,
              const std::pair<double, std::pair<int, std::string_view>>& s2) {
    if (std::abs(s1.first - s2.first) < EPS) {
        return s1.second.first < s2.second.first;
    }
    return s1.first > s2.first;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    if (results_count == 0) {
        return {};
    }
    std::map<std::string, size_t> exists_in_how_many_documents;
    std::set<std::string> query_words = DifferentWord(query);
    std::vector<std::pair<double, std::pair<size_t, std::string_view>>> current_answer;
    std::vector<std::string_view> all_documents = DocumentDec(text);
    for (std::string_view sv : all_documents) {
        std::set<std::string> words_inside = DifferentWord(sv);
        for (const std::string& word_in_doc : words_inside) {
            std::set<std::string>::iterator it1 = query_words.lower_bound(word_in_doc);
            if (it1 != query_words.end() && (*it1) == word_in_doc) {
                exists_in_how_many_documents[word_in_doc]++;
            }
        }
    }
    size_t current_number = 0;
    for (std::string_view sv : all_documents) {
        current_number++;
        std::map<std::string, size_t> all_document_words = DecompDocument(sv);
        size_t count_different_words = 0;
        for (std::pair<std::string, size_t> pr : all_document_words) {
            count_different_words += pr.second;
        }
        double current_value = 0;
        for (std::pair<std::string, size_t> pr : all_document_words) {
            double document_weight = (static_cast<double>(pr.second)) / (static_cast<double>(count_different_words));
            std::set<std::string>::iterator found_iterator = query_words.lower_bound(pr.first);
            if (found_iterator == query_words.end() || (*found_iterator) != pr.first) {
                continue;
            }
            size_t how_many_times_present = exists_in_how_many_documents[pr.first];
            double idf_weight =
                log(static_cast<double>(all_documents.size()) / static_cast<double>(how_many_times_present));
            current_value += idf_weight * document_weight;
        }
        if (current_value == 0) {
            continue;
        }
        current_answer.push_back(std::make_pair(current_value, std::make_pair(current_number, sv)));
    }
    sort(current_answer.begin(), current_answer.end(), Compare2);
    std::vector<std::string_view> returned_views;
    for (size_t index = 0; index < std::min(results_count, current_answer.size()); ++index) {
        returned_views.push_back(current_answer[index].second.second);
    }
    return returned_views;
}
