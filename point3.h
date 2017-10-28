#ifndef POINT3_H
#define POINT3_H
#include <cmath>
#include <cassert>
#include "vec3.h"
#include "normal.h"
class Point3 {
    public:
        float x;
        float y;
        float z;

        bool isNan() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        };

        Point3() { x = y = z = 0; };
        Point3(float _x) : x(_x), y(_x), z(_x) {
            assert(!isNan());
        };
        Point3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
            assert(!isNan());
        };

        float operator[](int i) const {
            if(i == 0) return x;
            else if(i == 1) return y;
            else if(i == 2) return z;
            else {
                std::cerr << "invalid index" << std::endl;
                std::exit(1);
            }
        };

        Point3 operator+(const Point3& p) const {
            return Point3(x + p.x, y + p.y, z + p.z);
        };
        Point3 operator+(const Vec3& v) const {
            return Point3(x + v.x, y + v.y, z + v.z);
        };
        Point3 operator+(const Normal& n) const {
            return Point3(x + n.x, y + n.y, z + n.z);
        };
        Point3 operator-(const Vec3& v) const {
            return Point3(x - v.x, y - v.y, z - v.z);
        };
        
        Vec3 operator-(const Point3& p) const {
            return Vec3(x - p.x, y - p.y, z - p.z);
        };

        Point3 operator-() const {
            return Point3(-x, -y, -z);
        };
};
inline Point3 operator*(float k, const Point3& p) {
    return Point3(k * p.x, k * p.y, k * p.z);
}
inline Point3 operator*(const Point3& p, float k) {
    return Point3(p.x * k, p.y * k, p.z * k);
}

inline float dot(const Point3& p, const Vec3& v) {
    return p.x*v.x + p.y*v.y + p.z*v.z;
}
inline float dot(const Vec3& v, const Point3& p) {
    return v.x*p.x + v.y*p.y + v.z*p.z;
}
inline float dot(const Point3& p, const Normal& n) {
    return p.x*n.x + p.y*n.y + p.z*n.z;
}
inline float dot(const Normal& n, const Point3& p) {
    return n.x*p.x + n.y*p.y + n.z*p.z;
}

inline float distance(const Point3& p1, const Point3& p2) {
    return (p1 - p2).length();
}
inline float distance2(const Point3& p1, const Point3& p2) {
    return (p1 - p2).length2();
}

inline Point3 lerp(float t, const Point3& p1, const Point3& p2) {
    return (1 - t)*p1 + t*p2;
};

inline Point3 min(const Point3& p1, const Point3& p2) {
    return Point3(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}
inline Point3 max(const Point3& p1, const Point3& p2) {
    return Point3(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::min(p1.z, p2.z));
}
#endif
