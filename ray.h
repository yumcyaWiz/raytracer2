#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class Ray {
    public:
        Vec3 origin;
        Vec3 direction;


        Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {};


        Vec3 operator()(float t) const {
            return origin + t*direction;
        };
};
#endif
