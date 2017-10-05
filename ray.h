#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class Ray {
    public:
        Vec3 origin;
        Vec3 direction;
        float tmin;
        float tmax;


        Ray() {};
        Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {
            tmin = 0.01f;
            tmax = 10000.0f;
        };


        Vec3 operator()(float t) const {
            return origin + t*direction;
        };
};
#endif
