#ifndef VEC2_H
#define VEC2_H
#include <iostream>
#include <cmath>
class Vec2 {
    public:
        float x;
        float y;

        Vec2() { x = y = 0.0f; };
        Vec2(float _x) : x(_x), y(_x) {};
        Vec2(float _x, float _y) : x(_x), y(_y) {};

        Vec2 operator+(const Vec2& v) const {
            return Vec2(x + v.x, y + v.y);
        };
        Vec2 operator+(float k) const {
            return Vec2(x + k, y + k);
        };
        Vec2 operator-(const Vec2& v) const {
            return Vec2(x - v.x, y - v.y);
        };
        Vec2 operator-(float k) const {
            return Vec2(x - k, y - k);
        };
        Vec2 operator*(const Vec2& v) const {
            return Vec2(x * v.x, y * v.y);
        };
        Vec2 operator*(float k) const {
            return Vec2(x * k, y * k);
        };
        Vec2 operator/(const Vec2& v) const {
            return Vec2(x / v.x, y / v.y);
        };
        Vec2 operator/(float k) const {
            return Vec2(x / k, y / k);
        };

        float length() {
            return std::sqrt(x*x + y*y);
        };
        float length2() {
            return x*x + y*y;
        };
};
Vec2 operator+(float k, const Vec2& v) {
    return Vec2(k + v.x, k + v.y);
}
Vec2 operator-(float k, const Vec2& v) {
    return Vec2(k - v.x, k - v.y);
}
Vec2 operator*(float k, const Vec2& v) {
    return Vec2(k * v.x, k * v.y);
}
Vec2 operator/(float k, const Vec2& v) {
    return Vec2(k / v.x, k / v.y);
}
std::ostream& operator<<(std::ostream& stream, const Vec2& v) {
    stream << "(" << v.x << ", " << v.y << ")" << std::endl;
}

float dot(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}
#endif
