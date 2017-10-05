#ifndef HIT_H
#define HIT_H
#include <memory>
#include "vec3.h"
#include "ray.h"
class Object;
class Hit {
    public:
        float t;
        Ray ray;
        Vec3 hitPos;
        Vec3 hitNormal;
        float u;
        float v;
        Object* hitObj;

        Hit() {};
};
#endif
