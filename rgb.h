#ifndef RGB_H
#define RGB_H
#include <cassert>
#include <cmath>
#include "vec3.h"
#include "normal.h"


float clamp(float x, float xmin, float xmax) {
    if(x < xmin)
        return xmin;
    else if(x > xmax)
        return xmax;
    else
        return x;
}



class RGB {
    public:
        float r;
        float g;
        float b;

        bool isNan() const {
            return std::isnan(r) || std::isnan(g) || std::isnan(b);
        };

        RGB() { r = g = b = 0; };
        RGB(float _r) : r(_r), g(_r), b(_r) {
            assert(!isNan());
        };
        RGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {
            assert(!isNan());
        };
        RGB(const Vec3& v) : r(v.x), g(v.y), b(v.z) {
            assert(!isNan());
        };
        RGB(const Normal& n) : r(n.x), g(n.y), b(n.z) {
            assert(!isNan());
        };


        RGB operator+(const RGB& c) const {
            return RGB(r + c.r, g + c.g, b + c.b);
        };
        RGB operator+(float k) const {
            return RGB(r + k, g + k, b + k);
        };
        RGB operator-(const RGB& c) const {
            return RGB(r - c.r, g - c.g, b - c.b);
        };
        RGB operator-(float k) const {
            return RGB(r - k, g - k, b - k);
        };
        RGB operator*(const RGB& c) const {
            return RGB(r * c.r, g * c.g, b * c.b);
        };
        RGB operator*(float k) const {
            return RGB(r * k, g * k, b * k);
        };
        RGB operator/(const RGB& c) const {
            return RGB(r / c.r, g / c.g, b / c.b);
        };
        RGB operator/(float k) const {
            return RGB(r / k, g / k, b / k);
        };
};
RGB operator+(float k, const RGB& c) {
    return RGB(k + c.r, k + c.g, k * c.b);
};
RGB operator-(float k, const RGB& c) {
    return RGB(k - c.r, k - c.g, k - c.b);
};
RGB operator*(float k, const RGB& c) {
    return RGB(k * c.r, k * c.g, k * c.b);
};
RGB operator/(float k, const RGB& c) {
    return RGB(k / c.r, k / c.g, k / c.b);
};


RGB clamp(const RGB& c, const RGB& cmin, const RGB& cmax) {
    return RGB(clamp(c.r, cmin.r, cmax.r), clamp(c.g, cmin.g, cmax.g), clamp(c.b, cmin.b, cmax.b));
}
RGB pow(const RGB& c, float p) {
    return RGB(std::pow(c.r, p), std::pow(c.g, p), std::pow(c.b, p));
}
#endif
