#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    if (number == 1) {
        return 1;
    }
    int64_t start_value = number;
    for (int64_t current_checking = 2; current_checking * current_checking <= number; ++current_checking) {
        if (number % current_checking == 0) {
            return current_checking;
        }
    }
    return start_value;
}
