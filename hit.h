#ifndef HIT_H
#define HIT_H
#include <memory>
#include "vec3.h"
#include "point3.h"
#include "normal.h"
#include "ray.h"
class Object;
class Hit {
    public:
        float t;
        Ray ray;
        Point3 hitPos;
        Normal hitNormal;
        float u;
        float v;
        Object* hitObj;
        bool inside;

        Hit() {};
        Hit(float _t, const Ray& _ray, const Point3& _hitPos, const Normal& _hitNormal, float _u, float _v, Object* _hitObj, bool _inside) : t(_t), ray(_ray), hitPos(_hitPos), hitNormal(_hitNormal), u(_u), v(_v), hitObj(_hitObj), inside(_inside) {};
};
#endif
