#ifndef VEC3_HPP
#define VEC3_HPP
#endif

#include <cmath>
#include <iostream>


class Vec3 {
    private:
        double x;
        double y;
        double z;
    public:
        Vec3() { x = 0; y = 0; z = 0; };
        Vec3(double _x) { x = _x; y = _x; z = _x; };
        Vec3(double _x, double _y, double _z) { x = _x; y = _y; z = _z; };
        ~Vec3() {};

        double getX() { return x; };
        double getY() { return y; };
        double getZ() { return z; };

        friend Vec3 operator+(const Vec3& v, const Vec3& v2);
        friend Vec3 operator+(double k, const Vec3& v);
        friend Vec3 operator+(const Vec3& v, double k);
        friend Vec3 operator-(const Vec3& v, const Vec3& v2);
        friend Vec3 operator-(double k, const Vec3& v);
        friend Vec3 operator-(const Vec3& v, double k);
        friend Vec3 operator*(const Vec3& v, const Vec3& v2);
        friend Vec3 operator*(double k, const Vec3& v);
        friend Vec3 operator*(const Vec3& v, double k);
        friend Vec3 operator/(const Vec3& v, const Vec3& v2);
        friend Vec3 operator/(double k, const Vec3& v);
        friend Vec3 operator/(const Vec3& v, double k);

        double dot(const Vec3& v) { return x*v.x + y*v.y + z*v.z; };
        Vec3 cross(const Vec3& v) {
            return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
        };

        double length() { return std::sqrt(x*x + y*y + z*z); };
        double length2() { return x*x + y*y + z*z; };

        void print() {
            std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
        };
};
Vec3 operator+(const Vec3& v, const Vec3& v2) {
    return Vec3(v.x + v2.x, v.y + v2.y, v.z + v2.z);
}
Vec3 operator+(double k, const Vec3& v) {
    return Vec3(k + v.x, k + v.y, k + v.z);
}
Vec3 operator+(const Vec3& v, double k) {
    return Vec3(k + v.x, k + v.y, k + v.z);
}
Vec3 operator-(const Vec3& v, const Vec3& v2) {
    return Vec3(v.x - v2.x, v.y - v2.y, v.z - v2.z);
}
Vec3 operator-(double k, const Vec3& v) {
    return Vec3(k - v.x, k - v.y, k - v.z);
}
Vec3 operator-(const Vec3& v, double k) {
    return Vec3(v.x - k, v.y - k, v.z - k);
}
Vec3 operator*(const Vec3& v, const Vec3& v2) {
    return Vec3(v.x * v2.x, v.y * v2.y, v.z * v2.z);
}
Vec3 operator*(double k, const Vec3& v) {
    return Vec3(k * v.x, k * v.y, k * v.z);
}
Vec3 operator*(const Vec3& v, double k) {
    return Vec3(k * v.x, k * v.y, k * v.z);
}
Vec3 operator/(const Vec3& v, const Vec3& v2) {
    return Vec3(v.x / v2.x, v.y / v2.y, v.z / v2.z);
}
Vec3 operator/(double k, const Vec3& v) {
    return Vec3(k / v.x, k / v.y, k / v.z);
}
Vec3 operator/(const Vec3& v, double k) {
    return Vec3(v.x / k, v.y / k, v.z / k);
}
