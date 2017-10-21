#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <cmath>
#include <cassert>
class Vec3 {
    public:
        float x;
        float y;
        float z;

        bool isNan() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        };

        Vec3() { x = y = z = 0; };
        Vec3(float _x) : x(_x), y(_x), z(_x) {
            assert(!isNan());
        };
        Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
            assert(!isNan());
        };

        Vec3 operator+(const Vec3& v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        };
        Vec3 operator+(float k) const {
            return Vec3(x + k, y + k, z + k);
        };
        Vec3 operator-(const Vec3& v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        };
        Vec3 operator-(float k) const {
            return Vec3(x - k, y - k, z - k);
        };
        Vec3 operator*(const Vec3& v) const {
            return Vec3(x * v.x, y * v.y, z * v.z);
        };
        Vec3 operator*(float k) const {
            return Vec3(x * k, y * k, z * k);
        };
        Vec3 operator/(const Vec3& v) const {
            return Vec3(x / v.x, y / v.y, z / v.z);
        };
        Vec3 operator/(float k) const {
            return Vec3(x / k, y / k, z / k);
        };

        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        };

        Vec3 setX(float _x) const {
            return Vec3(_x, y, z);
        };
        Vec3 setY(float _y) const {
            return Vec3(x, _y, z);
        };
        Vec3 setZ(float _z) const {
            return Vec3(x, y, _z);
        };

        float length() const {
            return std::sqrt(x*x + y*y + z*z);
        };
        float length2() const {
            return x*x + y*y + z*z;
        }
};
Vec3 operator+(float k, const Vec3& v) {
    return Vec3(k + v.x, k + v.y, k + v.z);
}
Vec3 operator-(float k, const Vec3& v) {
    return Vec3(k - v.x, k - v.y, k - v.z);
}
Vec3 operator*(float k, const Vec3& v) {
    return Vec3(k * v.x, k * v.y, k * v.z);
}
Vec3 operator/(float k, const Vec3& v) {
    return Vec3(k / v.x, k / v.y, k / v.z);
}
std::ostream& operator<<(std::ostream& stream, const Vec3& v) {
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}


inline float dot(const Vec3& v1, const Vec3& v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}


inline float distance(const Vec3& v1, const Vec3& v2) {
    return (v1 - v2).length();
};


inline Vec3 normalize(const Vec3& v) {
    return v/v.length();
};


inline Vec3 reflect(const Vec3& v_in, const Vec3& normal) {
    return v_in + 2.0*dot(-v_in, normal)*normal;
}
inline bool refract(const Vec3& v, const Vec3& n, float n1, float n2, Vec3& res) {
    float eta = n1/n2;
    float cosI = dot(-v, n);
    float sin2I = std::max(0.0, 1.0 - cosI*cosI);
    float sin2T = eta*eta*sin2I;
    if(sin2T >= 1.0)
        return false;
    float cosT = std::sqrt(1.0 - sin2T);
    res = eta*v + (eta*cosI - cosT)*n;
    return true;
}

#endif
