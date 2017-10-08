#ifndef NORMAL_H
#define NORMAL_H
#include <cmath>
#include "vec3.h"
class Normal {
    public:
        float x;
        float y;
        float z;

        Normal() { x = y = z = 0; };
        Normal(float _x) : x(_x), y(_x), z(_x) {};
        Normal(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
        Normal(const Vec3& v) : x(v.x), y(v.y), z(v.z) {};

        Normal operator+(const Normal& n) const {
            return Normal(x + n.x, y + n.y, z + n.z);
        };
        Normal operator+(float k) const {
            return Normal(x + k, y + k, z + k);
        };
        Normal operator-(const Normal& n) const {
            return Normal(x - n.x, y - n.y, z - n.z);
        };
        Normal operator-(float k) const {
            return Normal(x - k, y - k, z - k);
        };
        Normal operator*(const Normal& n) const {
            return Normal(x * n.x, y * n.y, z * n.z);
        };
        Normal operator*(float k) const {
            return Normal(x * k, y * k, z * k);
        };
        Normal operator/(const Normal& n) const {
            return Normal(x / n.x, y / n.y, z / n.z);
        };
        Normal operator/(float k) const {
            return Normal(x / k, y / k, z / k);
        };

        Normal operator-() const {
            return Normal(-x, -y, -z);
        };
};
Normal operator+(float k, const Normal& n) {
    return Normal(k + n.x, k + n.y, k + n.z);
}
Normal operator-(float k, const Normal& n) {
    return Normal(k - n.x, k - n.y, k - n.z);
}
Normal operator*(float k, const Normal& n) {
    return Normal(k * n.x, k * n.y, k * n.z);
}
Normal operator/(float k, const Normal& n) {
    return Normal(k / n.x, k / n.y, k / n.z);
}
Vec3 operator+(const Vec3& v, const Normal& n) {
    return Vec3(v.x + n.x, v.y + n.y, v.z + n.z);
}
Vec3 operator+(const Normal& n, const Vec3& v) {
    return Vec3(n.x + v.x, n.y + v.y, n.z + v.z);
}
Vec3 operator-(const Vec3& v, const Normal& n) {
    return Vec3(v.x - n.x, v.y - n.y, v.z - n.z);
}
Vec3 operator-(const Normal& n, const Vec3& v) {
    return Vec3(n.x - v.x, n.y - v.y, n.z - v.z);
}
Vec3 operator*(const Vec3& v, const Normal& n) {
    return Vec3(v.x * n.x, v.y * n.y, v.z * n.z);
}
Vec3 operator*(const Normal& n, const Vec3& v) {
    return Vec3(n.x * v.x, n.y * v.y, n.z * v.z);
}
Vec3 operator/(const Normal& n, const Vec3& v) {
    return Vec3(n.x / v.x, n.y / v.y, n.z / v.z);
}
Vec3 operator/(const Vec3& v, const Normal& n) {
    return Vec3(v.x / n.x, v.y / n.y, v.z / n.z);
}

inline float dot(const Normal& n1, const Normal& n2) {
    return n1.x*n2.x + n1.y*n2.y + n1.z*n2.z;
}
inline float dot(const Vec3& v, const Normal& n) {
    return v.x*n.x + v.y*n.y + v.z*n.z;
}
inline float dot(const Normal& n, const Vec3& v) {
    return n.x*v.x + n.y*v.y + n.z*v.z;
}

inline Vec3 reflect(const Vec3& v_in, const Normal& normal) {
    return v_in + 2.0*dot(-v_in, normal)*normal;
}
inline bool refract(const Vec3& v, const Normal& n, float n1, float n2, Vec3& res) {
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
