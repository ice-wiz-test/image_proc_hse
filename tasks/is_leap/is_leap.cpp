#include "is_leap.h"

const int kMostImportantConstant = 400;
const int kUsualConstant = 4;
const int kCancelConstant = 100;
bool IsLeap(int year) {
    if (year % kMostImportantConstant == 0)
        return true;
    else {
        if (year % kCancelConstant == 0)
            return false;
        else {
            if (year % kUsualConstant == 0)
                return true;
            else {
                return false;
            }
        }
    }
}
