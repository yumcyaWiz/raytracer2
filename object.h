#ifndef OBJECT_H
#define OBJECT_H
#include <cmath>
#include "vec2.h"
#include "vec3.h"
#include "point3.h"
#include "normal.h"
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "texture.h"
#include "transform.h"
#include "util.h"
class Object {
    public:
        const Material* mat;
        const Texture* tex;
        const Transform* objectToWorld;
        const Transform*  worldToObject;

        Object(Transform* _objectToWorld, Transform* _worldToObject, Material* _mat, Texture* _tex) : mat(_mat), tex(_tex), objectToWorld(_objectToWorld), worldToObject(_worldToObject) {};

        virtual bool intersect(const Ray& ray, Hit& res) const = 0;
};


class Sphere : public Object {
    public:
        const float radius;
        const float ymin;
        const float ymax;
        const float phi_max;
        const float theta_min;
        const float theta_max;


        Sphere(float _radius, Transform* _objectToWorld, Transform* _worldToObject, Material* _mat, Texture* _tex, float _ymin, float _ymax, float _phi_max) : Object(_objectToWorld, _worldToObject, _mat, _tex), radius(_radius), ymin(clamp(std::min(_ymin, _ymax), -_radius, _radius)), ymax(clamp(std::max(_ymin, _ymax), -_radius, _radius)), phi_max(_phi_max), theta_min(std::acos(clamp(ymin/radius, -1, 1))), theta_max(std::acos(clamp(ymax/radius, -1, 1))) {};


        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float a = ray.direction.length2();
            float b = 2.0*dot(ray.origin, ray.direction);
            float c = (ray.origin - Point3()).length2() - radius*radius;
            float D = b*b - 4*a*c;

            if(D < 0)
                return false;
            float t0 = (-b - std::sqrt(D))/(2.0*a);
            float t1 = (-b + std::sqrt(D))/(2.0*a);
            if(t0 < ray.tmin || t1 > ray.tmax)
                return false;
            float t = t0;
            if(t < ray.tmin) {
                t = t1;
                if(t > ray.tmax)
                    return false;
            }

            Point3 hitPos = ray(t);
            if(hitPos.x == 0 && hitPos.z == 0) hitPos.x = 1e-5*radius;
            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;

            if((ymin > -radius && hitPos.y < ymin) || (ymax < radius && hitPos.y > ymax) || phi > phi_max) {
                if(t == t1) return false;

                if(t1 > ray.tmax) return false;
                t = t1;
                hitPos = ray(t);
                if(hitPos.x == 0 && hitPos.z == 0) hitPos.x = 1e-5*radius;
                phi = std::atan2(hitPos.z, hitPos.x);
                if(phi < 0) phi += 2*M_PI;

                if((ymin > -radius && hitPos.y < ymin) || (ymax < radius && hitPos.y > ymax) || phi > phi_max)
                    return false;
            }

            res.hitNormal = Normal(normalize(hitPos - Point3()));
            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;

            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Sphere*>(this);

            res.u = phi/phi_max;
            float theta = std::acos(clamp(hitPos.y/radius, -1, 1));
            res.v = (theta - theta_min)/(theta_max - theta_min);

            res = (*objectToWorld)(res);

            return true;
        };
};


class Plane : public Object {
    public:
        Plane(Transform* _objectToWorld, Transform* _worldToObject, Material* mat, Texture* tex) : Object(_objectToWorld, _worldToObject, mat, tex) {};

        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float t = -ray.origin.y/ray.direction.y;
            if(t < ray.tmin || t > ray.tmax)
                return false;

            t -= 1e-5;
            Point3 hitPos = ray(t);
            if(std::abs(hitPos.x) > 1 || std::abs(hitPos.z) > 1)
                return false;

            res.t = t;
            res.ray = ray;
            res.hitPos = hitPos;
            res.hitNormal = Normal(0, 1, 0);
            res.hitObj = const_cast<Plane*>(this);
            res.inside = false;
            if(dot(ray.direction, res.hitNormal) > 0) {
                res.hitNormal = -res.hitNormal;
            }
            res.u = (hitPos.x + 1.0)/2.0; 
            res.v = (hitPos.z + 1.0)/2.0;

            res = (*objectToWorld)(res);

            return true;
        };
};


class Cylinder : public Object {
    public:
        float ymin;
        float ymax;
};
class Box : public Object {
};
class Cone : public Object {
};
#endif
