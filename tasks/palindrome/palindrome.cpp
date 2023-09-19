#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t front_iterator = 0;
    size_t last_iterator = str.size();
    last_iterator--;  // не переполняется, так как str.size() >= 1
    while (front_iterator < last_iterator) {
        while (front_iterator < last_iterator && str[front_iterator] == ' ') {
            front_iterator++;
        }
        if (front_iterator == last_iterator) {
            break;
        }
        while (last_iterator > front_iterator && str[last_iterator] == ' ') {
            last_iterator--;
        }
        if (front_iterator == last_iterator) {
            break;
        }
        if (str[last_iterator] != str[front_iterator]) {
            return false;
        }
        front_iterator++;
        last_iterator--;
    }
    return true;
}
