#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    int64_t a = height;
    a = a * width;
    if(a <= slices_amount) return false;
    if(slices_amount % height == 0) return true;
    if(slices_amount % width == 0) return true;
    return false;
};