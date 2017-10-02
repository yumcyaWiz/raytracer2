#ifndef OBJECT_H
#define OBJECT_H
#include "vec3.h"
#include "ray.h"
class Object {
    public:
        Vec3 pos;
        virtual bool intersect(const Ray& ray, Hit& res) = 0;
};
class Sphere : public Object {
    public:
        float radius;


        Sphere(const Vec3& center, float _radius) : pos(center), radius(_radius) {};


        bool intersect(const Ray& ray, Hit& res) {
            float b = 
        };
}
#endif
