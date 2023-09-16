#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int current_val = 1;
    int prev_val = 0;
    for(int count = 2; count <= n; ++count) {
        std::swap(current_val, prev_val);
        current_val += prev_val;
    }
    return current_val;
}
