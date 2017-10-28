#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <chrono>
#include <ctime>

#include "rgb.h"



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


RGB hsv2rgb(float h, float s, float v) {
    float C = v * s;
    float H = h/60.0;
    float X = C * (1 - std::abs(std::fmod(H, 2.0f) - 1.0f));
    RGB col;
    if(H >= 0 && H <= 1)
        col = RGB(C, X, 0);
    else if(H >= 1 && H <= 2)
        col = RGB(X, C, 0);
    else if(H >= 2 && H <= 3)
        col = RGB(0, C, X);
    else if(H >= 3 && H <= 4)
        col = RGB(0, X, C);
    else if(H >= 4 && H <= 5)
        col = RGB(X, 0, C);
    else if(H >= 5 && H <= 6)
        col = RGB(C, 0, X);
    else
        col = RGB(0, 0, 0);
    float m = v - C;
    return RGB((col.r + m), (col.g + m), (col.b + m));
}
#endif
