#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <chrono>
#include <ctime>
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

std::string ctime_string() {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::string str = std::ctime(&t);
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == ' ')
            str[i] = '_';
    }
    return str;
}
#endif
