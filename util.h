#ifndef UTIL_H
#define UTIL_H
float clamp(float x, float xmin, float xmax) {
    if(x < xmin)
        return xmin;
    else if(x > xmax)
        return xmax;
    else
        return x;
}
#endif
