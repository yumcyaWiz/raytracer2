#ifndef OBJECT_H
#define OBJECT_H
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "texture.h"
class Object {
    public:
        std::shared_ptr<Material> mat;
        std::shared_ptr<Texture> tex;

        Object(Material* _mat, Texture* _tex) : mat(std::shared_ptr<Material>(_mat)), tex(std::shared_ptr<Texture>(_tex)) {};

        virtual bool intersect(const Ray& ray, Hit& res) = 0;
};
class Sphere : public Object {
    public:
        float radius;
        float theta_min;
        float theta_max;
        float phi_min;
        float phi_max;
        Vec3 center;


        Sphere(const Vec3& _center, float _radius, Material* _mat, Texture* _tex, float _theta_min = 0.0f, float _theta_max = M_PI, float _phi_min = 0.0f, float _phi_max = 2.0f*M_PI) : Object(_mat, _tex), center(_center), radius(_radius), 
        theta_min(_theta_min), theta_max(_theta_max), phi_min(_phi_min), phi_max(_phi_max) {};


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
                t = t1;
            }
            if(t < ray.tmin || t > ray.tmax) {
                return false;
            }
            res.t = t;
            res.ray = ray;
            res.hitPos = ray(t);
            res.hitNormal = normalize(res.hitPos - center);
            res.hitObj = this;

            float phi = std::atan2(res.hitNormal.z, res.hitNormal.x) + M_PI;
            float theta = std::atan(res.hitNormal.y/std::sqrt(res.hitNormal.x*res.hitNormal.x + res.hitNormal.z*res.hitNormal.z)) + M_PI/2.0f;
            if(theta < theta_min || theta > theta_max || phi < phi_min || phi > phi_max)
                return false;
            res.u = phi/(2.0f*M_PI);
            res.v = theta/M_PI;

            return true;
        };
};
class Box : public Object {
};
class Cone : public Object {
};
#endif
