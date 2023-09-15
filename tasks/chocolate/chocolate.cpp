#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if(height <=0 || width <= 0 || slices_amount < 0) return false;
    if(slices_amount == 0) return false;
    int required_minimum = slices_amount / width;
    if(required_minimum >= height) return false;
    if(slices_amount % height == 0) return true;
    if(slices_amount % width == 0) return true;
    return false;
};