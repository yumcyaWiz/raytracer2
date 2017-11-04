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
        float u;
        float v;
        Vec3 dpdu;
        Vec3 dpdv;
        Normal hitNormal;
        Object* hitObj;
        bool inside;

        Hit() {};
        Hit(float _t, const Ray& _ray, const Point3& _hitPos, float _u, float _v, const Vec3& dpdu, const Vec3& dpdv, const Normal& hitNormal, Object* _hitObj, bool _inside) : t(_t), ray(_ray), hitPos(_hitPos), u(_u), v(_v), dpdu(dpdu), dpdv(dpdv), hitNormal(hitNormal), hitObj(_hitObj), inside(_inside) {};
};
#endif
