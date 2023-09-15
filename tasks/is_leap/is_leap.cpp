#include "is_leap.h"

bool IsLeap(int year) {
    if(year < 0) year = -year - 3;
    if(year % 400 == 0) return true;
    else {
        if(year % 100 == 0) return false;
        else {
            if(year % 4 == 0) return true;
            else return false;
        }
    }
}
