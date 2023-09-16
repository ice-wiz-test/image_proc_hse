#include "password.h"

const char K_MINIMUM_LETTER = 'a';
const char K_MAXIMUM_LETTER = 'z';
const char K_BIG_MINIMUM_LETTER = 'A';
const char K_BIG_MAXIMUM_LETTER = 'Z';
const char K_MINIMUM_DIGIT = '0';
const char K_MAXIMUM_DIGIT = '9';

bool IsSmallLetter(char a) {
    if (K_MINIMUM_LETTER <= a && a <= K_MAXIMUM_LETTER) {
        return true;
    }
    return false;
}

bool IsBigLetter(char a) {
    if (K_BIG_MINIMUM_LETTER <= a && a <= K_BIG_MAXIMUM_LETTER) {
        return true;
    }
    return false;
}

bool IsDigit(char a) {
    if (K_MINIMUM_DIGIT <= a && a <= K_MAXIMUM_DIGIT) {
        return true;
    }
    return false;
}

bool ValidatePassword(const std::string& password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    }
    size_t count_small_letters = 0;
    size_t count_digits = 0;
    size_t count_big_letters = 0;
    size_t count_other = 0;
    for (size_t iter = 0; iter < password.size(); ++iter) {
        int code = static_cast<int>(password[iter]);
        if (code < 33 || code > 126) {
            return false;
        }
        if (IsSmallLetter(password[iter])) {
            count_small_letters++;
            continue;
        }
        if (IsBigLetter(password[iter])) {
            count_big_letters++;
            continue;
        }
        if (IsDigit(password[iter])) {
            count_digits++;
            continue;
        }
        count_other++;
    }
    int total_count = 0;
    if (count_small_letters != 0) {
        total_count++;
    }
    if (count_big_letters != 0) {
        total_count++;
    }
    if (count_digits != 0) {
        total_count++;
    }
    if (count_other != 0) {
        total_count++;
    }
    if (total_count >= 3) {
        return true;
    }
    return false;
}
