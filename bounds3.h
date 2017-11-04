#ifndef BOUNDS3_H
#define BOUNDS3_H
#include "point3.h"
class Bounds3 {
    public:
        Point3 pMin;
        Point3 pMax;

        Bounds3() {
            float minNum = std::numeric_limits<float>::lowest();
            float maxNum = std::numeric_limits<float>::max();
            pMin = Point3(minNum, minNum, minNum);
            pMax = Point3(maxNum, maxNum, maxNum);
        };
        Bounds3(const Point3& p) : pMin(p), pMax(p) {};
        Bounds3(const Point3& p1, const Point3& p2) : pMin(Point3(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z))), pMax(Point3(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z))) {};
};


inline Union(const Bounds3& b, const Point3& p) {
    return Bounds3(Point3(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y), std::min(b.pMin.z, p.z)), Point3(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y), std::max(b.pMax.z, p.z)));
}
inline Union(const Bounds3& b1, const Bounds3& b2) {
    return Bounds3(Point3(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y), std::min(b1.pMin.z, b2.pMin.z)), Point3(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y), std::max(b1.pMax.z, b2.pMax.z)));
}
inline Intersect(const Bounds3& b1, const Bounds3& b2) {
    return Bounds3(Point3(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y), std::max(b1.pMin.z, b2.pMin.z)), Point3(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y), std::min(b1.pMax.z, b2.pMax.z)));
}
inline bool Overlaps(const Bounds3& b1, const Bounds3& b2) {
    bool x = (b1,pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
    bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
    bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.x <= b2.pMax.z);
    return (x && y && z);
}

inline bool Inside(const Point3& p, const Bounds3& b) {
    return (p.x >= b.pMin.x && p.x <= b.pMax.x && p.y >= b.pMin.y && p.y <= b.pMax.y && p.z >= b.pMin.z && p.z <= b.pMax.z);
}
