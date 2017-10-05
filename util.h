#ifndef UTIL_H
#define UTIL_H
#include <string>
float clamp(float x, float xmin, float xmax) {
    if(x < xmin)
        return xmin;
    else if(x > xmax)
        return xmax;
    else
        return x;
}

std::string percentage(double x, double max) {
    return std::to_string(x/max*100) + "%";
}
std::string progressbar(double x, double max) {
    int max_count = 40;
    int cur_count = (int)(x/max*max_count);
    std::string str;
    str += "[";
    for(int i = 0; i < cur_count; i++) {
        str += "#";
    }
    for(int i = 0; i < (max_count - cur_count - 1); i++) {
        str += " ";
    }
    str += "]";
    return str;
}

#endif
