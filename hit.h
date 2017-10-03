#ifndef HIT_H
#define HIT_H
#include "vec3.h"
#include "ray.h"
class Hit {
    public:
        float t;
        Ray ray;
        Vec3 hitPos;
        Vec3 hitNormal;


        Hit() {};
        Hit(float _t, const Ray& _ray, const Vec3& _hitPos, const Vec3& _hitNormal) : t(_t), ray(_ray), hitPos(_hitPos), hitNormal(_hitNormal) {};
};
#endif
