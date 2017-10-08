#ifndef RAY_H
#define RAY_H
#include "vec3.h"
#include "point3.h"
class Ray {
    public:
        Point3 origin;
        Vec3 direction;
        float tmin;
        float tmax;


        Ray() {};
        Ray(const Point3& o, const Vec3& d) : origin(o), direction(d) {
            tmin = 0.01f;
            tmax = 10000.0f;
        };


        Point3 operator()(float t) const {
            return origin + t*direction;
        };
};
#endif
