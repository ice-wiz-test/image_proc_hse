#include "is_leap.h"

const int K_MOST_IMPORTANT_CONSTANT = 400;
const int K_USUAL_CONSTANT = 4;
const int K_CANCEL_CONSTANT = 100;

bool IsLeap(int year) {
    if (year % K_MOST_IMPORTANT_CONSTANT == 0) {
        return true;
    }
    if (year % K_CANCEL_CONSTANT == 0) {
        return false;
    }
    if (year % K_USUAL_CONSTANT == 0) {
        return true;
    }
    return false;
}
