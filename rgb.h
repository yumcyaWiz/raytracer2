#ifndef RGB_H
#define RGB_H
#include "util.h"
class RGB {
    public:
        float r;
        float g;
        float b;


        RGB() { r = g = b = 0; };
        RGB(float _r) : r(_r), g(_r), b(_r) {};
        RGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {};
        RGB(const Vec3& v) : r(v.x), g(v.y), b(v.z) {};


        RGB operator+(const RGB& c) const {
            return RGB(r + c.r, g + c.g, b + c.b);
        };
        RGB operator-(const RGB& c) const {
            return RGB(r - c.r, g - c.g, b - c.b);
        };
        RGB operator*(const RGB& c) const {
            return RGB(r * c.r, g * c.g, b * c.b);
        };
        RGB operator/(const RGB& c) const {
            return RGB(r / c.r, g / c.g, b / c.b);
        };
};


RGB clamp(const RGB& c, const RGB& cmin, const RGB& cmax) {
    return RGB(clamp(c.r, cmin.r, cmax.r), clamp(c.g, cmin.g, cmax.g), clamp(c.b, cmin.b, cmax.b));
}
#endif
