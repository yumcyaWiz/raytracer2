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
class Object {
    public:
        std::shared_ptr<Material> mat;
        std::shared_ptr<Texture> tex;
        std::shared_ptr<Transform> objectToWorld;
        std::shared_ptr<Transform> worldToObject;

        Object(Transform* _objectToWorld, Transform* _worldToObject, Material* _mat, Texture* _tex) {
            mat = std::shared_ptr<Material>(_mat);
            tex = std::shared_ptr<Texture>(_tex);
            objectToWorld = std::shared_ptr<Transform>(_objectToWorld);
            worldToObject = std::shared_ptr<Transform>(_worldToObject);
        };

        virtual bool intersect(const Ray& ray, Hit& res) const = 0;
};


class Sphere : public Object {
    public:
        float radius;
        float theta_min;
        float theta_max;
        float phi_min;
        float phi_max;


        Sphere(float _radius, Transform* _objectToWorld, Transform* _worldToObject, Material* _mat, Texture* _tex, float _theta_min = 0.0f, float _theta_max = M_PI, float _phi_min = 0.0f, float _phi_max = 2.0f*M_PI) : Object(_objectToWorld, _worldToObject, _mat, _tex), radius(_radius), theta_min(_theta_min), theta_max(_theta_max), phi_min(_phi_min), phi_max(_phi_max) {};


        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float a = ray.direction.length2();
            float b = 2.0*dot(ray.origin, ray.direction);
            float c = (ray.origin - Point3()).length2() - radius*radius;
            float D = b*b - 4*a*c;
            if(D < 0)
                return false;
            float t1 = (-b + std::sqrt(D))/(2.0*a);
            float t2 = (-b - std::sqrt(D))/(2.0*a);
            float t = t2;
            if(t < ray.tmin || t > ray.tmax) {
                t = t1;
            }
            if(t < ray.tmin || t > ray.tmax) {
                return false;
            }

            Point3 hitPos = ray(t);
            res.hitNormal = Normal(normalize(hitPos - Point3()));
            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;

            hitPos = hitPos + 1e-5*res.hitNormal;
            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Sphere*>(this);

            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            float theta = std::acos(hitPos.y/radius);
            if(theta < theta_min || theta > theta_max || phi < phi_min || phi > phi_max)
                return false;
            res.u = (phi - phi_min)/(phi_max - phi_min);
            res.v = 1.0 - (theta - theta_min)/(theta_max - theta_min);

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
class Box : public Object {
};
class Cone : public Object {
};
#endif
