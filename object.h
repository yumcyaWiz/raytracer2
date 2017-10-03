#ifndef OBJECT_H
#define OBJECT_H
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hit.h"
class Object {
    public:
        virtual bool intersect(const Ray& ray, Hit& res) = 0;
};
class Sphere : public Object {
    public:
        float radius;
        Vec3 center;


        Sphere(const Vec3& _center, float _radius) : center(_center), radius(_radius) {};


        bool intersect(const Ray& ray, Hit& res) {
            float b = dot(ray.direction, ray.origin - center);
            float c = (ray.origin - center).length2() - radius*radius;
            float D = b*b - c;
            if(D < 0)
                return false;
            float t1 = -b + std::sqrt(D);
            float t2 = -b - std::sqrt(D);
            float t = t2;
            if(t < ray.tmin || t > ray.tmax) {
                t = t2;
            }
            if(t < ray.tmin || t > ray.tmax) {
                return false;
            }
            res.t = t;
            res.ray = ray;
            res.hitPos = ray(t);
            res.hitNormal = normalize(res.hitPos - center);
            return true;
        };
};
#endif
