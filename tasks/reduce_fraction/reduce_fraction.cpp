#include "reduce_fraction.h"

int64_t NOD(int64_t a, int64_t b) {
    if (b == 0) {
        return a;
    }
    return NOD(b, a % b);
}

int64_t AbsoluteValue(int64_t a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    if (denominator < 0) {
        denominator = denominator * (-1);
        numerator = numerator * (-1);
    }
    int64_t BiggestCommonDivisor = NOD(AbsoluteValue(numerator), AbsoluteValue(denominator));
    numerator = numerator / BiggestCommonDivisor;
    denominator = denominator / BiggestCommonDivisor;
    return numerator + denominator;
}
