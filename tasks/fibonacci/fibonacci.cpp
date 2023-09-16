#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int64_t current_val = 1;
    int64_t prev_val = 0;
    for(int count = 2; count <= n; ++count) {
        int next_member = current_val + prev_val;
        prev_val = current_val;
        current_val = next_member;
    }
    return current_val;
}
