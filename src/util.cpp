#include "util.h"

int clamp(int val, int min, int max){
    val = std::min(max, val);
    val = std::max(min, val);
    return val;
}

