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


        Sphere(Transform* _objectToWorld, Transform* _worldToObject, Material* _mat, Texture* _tex, float _radius, float _ymin, float _ymax, float _phi_max) : Object(_objectToWorld, _worldToObject, _mat, _tex), radius(_radius), ymin(clamp(std::min(_ymin, _ymax), -_radius, _radius)), ymax(clamp(std::max(_ymin, _ymax), -_radius, _radius)), phi_max(_phi_max), theta_min(std::acos(clamp(ymin/radius, -1, 1))), theta_max(std::acos(clamp(ymax/radius, -1, 1))) {};


        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float a = ray.direction.length2();
            float b = 2.0f*dot(ray.origin, ray.direction);
            float c = (ray.origin - Point3()).length2() - radius*radius;
            float D = b*b - 4.0f*a*c;

            if(D < 0)
                return false;
            float t0 = (-b - std::sqrt(D))/(2.0*a);
            float t1 = (-b + std::sqrt(D))/(2.0*a);
            if(t0 > ray.tmax || t1 < ray.tmin)
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


            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Sphere*>(this);

            res.u = phi/phi_max;
            res.u = 1.0f - res.u;
            float theta = std::acos(clamp(hitPos.y/radius, -1, 1));
            res.v = (theta - theta_min)/(theta_max - theta_min);
            res.v = 1.0f - res.v;

            Vec3 dpdu = Vec3(-phi_max*hitPos.z, 0, phi_max*hitPos.x);
            Vec3 dpdv = (theta_max - theta_min) * Vec3(hitPos.y*std::cos(phi), -radius*std::sin(theta), hitPos.y*std::sin(phi));
            res.dpdu = dpdu;
            res.dpdv = dpdv;
            res.hitNormal = -cross(dpdu, dpdv);
            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;

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
            res.hitNormal = Normal(0, 1, 0);
            res.inside = false;
            if(dot(ray.direction, res.hitNormal) > 0) {
                res.hitNormal = -res.hitNormal;
            }
            res.hitPos = ray(t);
            res.u = (hitPos.x + 1.0)/2.0; 
            res.v = (hitPos.z + 1.0)/2.0;
            res.hitObj = const_cast<Plane*>(this);

            res = (*objectToWorld)(res);

            return true;
        };
};


class Cylinder : public Object {
    public:
        const float radius;
        const float yMin;
        const float yMax;
        const float phiMax;

        Cylinder(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const float radius, const float yMin, const float yMax, const float phiMax) : Object(objectToWorld, worldToObject, mat, tex), radius(radius), yMin(yMin), yMax(yMax), phiMax(phiMax) {};

        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float a = ray.direction.x*ray.direction.x + ray.direction.z*ray.direction.z;
            float b = 2*(ray.direction.x*ray.origin.x + ray.direction.z*ray.origin.z);
            float c = ray.origin.x*ray.origin.x + ray.origin.z*ray.origin.z - radius*radius;
            float D = b*b - 4*a*c;
            if(D < 0) return false;
            float t0 = (-b - std::sqrt(D))/(2*a);
            float t1 = (-b + std::sqrt(D))/(2*a);
            Point3 hitPos;
            float phi;
            if(t0 > ray.tmax || t1 < ray.tmin) return false;
            float t = t0;
            hitPos = ray(t);
            phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            if(t < ray.tmin || hitPos.y < yMin || hitPos.y > yMax || phi > phiMax) {
                t = t1;
                hitPos = ray(t);
                phi = std::atan2(hitPos.z, hitPos.x);
                if(phi < 0) phi += 2*M_PI;
                if(t > ray.tmax || hitPos.y < yMin || hitPos.y > yMax || phi > phiMax) return false;
            }

            res.t = t;
            res.hitPos = hitPos;
            res.ray = ray;
            res.hitObj = const_cast<Cylinder*>(this);

            res.u = phi/phiMax;
            res.u = 1.0f - res.u;
            res.v = (hitPos.y - yMin)/(yMax - yMin);
            res.v = 1.0f - res.v;

            Vec3 dpdu = Vec3(-phiMax*hitPos.z, 0, phiMax*hitPos.x);
            Vec3 dpdv = Vec3(0, yMax - yMin, 0);

            res.dpdu = dpdu;
            res.dpdv = dpdv;
            res.hitNormal = -cross(dpdu, dpdv);
            res.inside = false;
            if(dot(ray.direction, res.hitNormal) > 0)
                res.hitNormal = -res.hitNormal;
            res = (*objectToWorld)(res);
            return true;
        };
};
class Box : public Object {
    public:
        const Point3 pMin;
        const Point3 pMax;

        Box(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const Point3& pMin, const Point3& pMax) : Object(objectToWorld, worldToObject, mat, tex), pMin(pMin), pMax(pMax) {};

        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float t0 = ray.tmin;
            float t1 = ray.tmax + 1.0f;
            Normal n;
            for(int i = 0; i < 3; i++) {
                float invDir = 1.0f/ray.direction[i];
                if(std::isnan(invDir))
                    continue;
                float tNear = (pMin[i] - ray.origin[i])*invDir;
                float tFar = (pMax[i] - ray.origin[i])*invDir;
                if(tNear > tFar) std::swap(tNear, tFar);
                if(tNear > t0) {
                    t0 = tNear;
                    if(i == 0) n = Normal(1, 0, 0);
                    else if(i == 1) n = Normal(0, 1, 0);
                    else n = Normal(0, 0, 1);
                }
                t1 = tFar < t1 ? tFar : t1;
                if(t0 > t1) return false;
            }
            if(t0 <= ray.tmin || t0 >= ray.tmax) return false;

            Point3 hitPos = ray(t0);
            res.t = t0;
            res.hitPos = hitPos;
            res.hitNormal = n;
            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside) {
                res.hitNormal = -res.hitNormal;
            }
            res.ray = ray;
            res.hitObj = const_cast<Box*>(this);
            res = (*objectToWorld)(res);
            return true;
        };
};
class Disk : public Object {
    public:
        const float height;
        const float radius;
        const float innerRadius;
        const float phiMax;

        Disk(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const float height, const float radius, const float innerRadius, const float phiMax) : Object(objectToWorld, worldToObject, mat, tex), height(height), radius(radius), innerRadius(innerRadius), phiMax(phiMax) {};

        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float t = (height - ray.origin.y)/ray.direction.y;
            if(t < ray.tmin || t > ray.tmax) return false;
            Point3 hitPos = ray(t);
            float dist2 = hitPos.x*hitPos.x + hitPos.z*hitPos.z;
            if(dist2 < innerRadius*innerRadius || dist2 > radius*radius) return false;
            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            if(phi > phiMax) return false;

            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Disk*>(this);

            res.u = phi/phiMax;
            float rHit = std::sqrt(dist2);
            res.v = (rHit - innerRadius)/(radius - innerRadius);
            res.v = 1.0f - res.v;

            res.dpdu = Vec3(-phiMax*hitPos.z, 0, phiMax*hitPos.x);
            res.dpdv = (radius - innerRadius) * Vec3(hitPos.x, 0, hitPos.z);
            res.hitNormal = -cross(res.dpdu, res.dpdv);
            res.inside = false;
            res = (*objectToWorld)(res);

            return true;
        };
};
class Cone : public Object {
    public:
        const float height;
        const float radius;
        const float phiMax;

        Cone(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const float height, const float radius, const float phiMax) : Object(objectToWorld, worldToObject, mat, tex), height(height), radius(radius), phiMax(phiMax) {};

        bool intersect(const Ray& ra, Hit& res) const {
            Ray ray = (*worldToObject)(ra);
            float dx = ray.direction.x;
            float dy = ray.direction.y;
            float dz = ray.direction.z;
            float ox = ray.origin.x;
            float oy = ray.origin.y;
            float oz = ray.origin.z;
            float h = height;
            float r = radius;

            float a = (h*h)/(r*r)*(dx*dx + dz*dz) - dy*dy;
            float b = 2*(h*h)/(r*r)*(ox*dx + oz*dz) - 2*dy*(oy - h);
            float c = (h*h)/(r*r)*(ox*ox + oz*oz) - (oy*oy - 2*h*oy + h*h);
            float D = b*b - 4*a*c;
            if(D < 0) return false; 
            float t0 = (-b - std::sqrt(D))/(2*a);
            float t1 = (-b + std::sqrt(D))/(2*a);
            if(t0 > ray.tmax || t1 < ray.tmin || std::isnan(t0) || std::isnan(t1)) return false;
            float t = t0;
            Point3 hitPos = ray(t);
            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            if(t < ray.tmin || hitPos.y > height || hitPos.y < 0 || phi > phiMax) {
                t = t1;
                hitPos = ray(t);
                phi = std::atan2(hitPos.z, hitPos.x);
                if(phi < 0) phi += 2*M_PI;
                if(t > ray.tmax || hitPos.y > height || hitPos.y < 0|| phi > phiMax) return false;
            }

            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Cone*>(this);

            res.u = phi/phiMax;
            res.v = std::min(hitPos.y/height, 1.0f) - 0.001f;
            Vec3 dpdu = Vec3(-phiMax*hitPos.z, 0, phiMax*hitPos.x);
            Vec3 dpdv = Vec3(-hitPos.x/(1.0f - res.v), height, -hitPos.z/(1.0f - res.v));
            res.dpdu = dpdu;
            res.dpdv = dpdv;
            res.hitNormal = -cross(dpdu, dpdv);
            
            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;
            
            res = (*objectToWorld)(res);
            return true;
        };
};


class Paraboloid : public Object {
    public:
        const float height;
        const float radius;
        const float yMin;
        const float yMax;
        const float phiMax;

        Paraboloid(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const float height, const float radius, const float yMin, const float yMax, const float phiMax) : Object(objectToWorld, worldToObject, mat, tex), height(height), radius(radius), yMin(yMin), yMax(yMax), phiMax(phiMax) {};

        bool intersect(const Ray& ra, Hit& res) const {
            Ray ray = (*worldToObject)(ra);
            float ox = ray.origin.x;
            float oy = ray.origin.y;
            float oz = ray.origin.z;
            float dx = ray.direction.x;
            float dy = ray.direction.y;
            float dz = ray.direction.z;
            float r = radius;
            float h = height;
            
            float a = h/(r*r)*(dx*dx + dz*dz);
            float b = 2*h/(r*r)*(ox*dx + oz*dz) - dy;
            float c = h/(r*r)*(ox*ox + oz*oz) - oy;
            float D = b*b - 4*a*c;
            if(D < 0) return false;
            float t0 = (-b - std::sqrt(D))/(2*a);
            float t1 = (-b + std::sqrt(D))/(2*a);
            if(t0 > ray.tmax || t1 < ray.tmin) return false;
            float t = t0;
            Point3 hitPos = ray(t);
            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            if(t < ray.tmin || hitPos.y < yMin || hitPos.y > yMax || phi > phiMax) {
                t = t1;
                hitPos = ray(t);
                phi = std::atan2(hitPos.z, hitPos.x);
                if(phi < 0) phi += 2*M_PI;
                if(t > ray.tmax || hitPos.y < yMin || hitPos.y > yMax || phi > phiMax) return false;
            }

            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Paraboloid*>(this);

            res.u = 1.0f - phi/phiMax;
            res.v = 1.0f - (hitPos.y - yMin)/(yMax - yMin);
            Vec3 dpdu = Vec3(-phiMax*hitPos.z, 0, phiMax*hitPos.x);
            Vec3 dpdv = (yMax - yMin) * Vec3(hitPos.x/(2*hitPos.y), 1, hitPos.z/(2*hitPos.y));
            res.dpdu = dpdu;
            res.dpdv = dpdv;
            res.hitNormal = -cross(dpdu, dpdv);

            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;

            res = (*objectToWorld)(res);
            return true;
        };
};


class Hyperboloid : public Object {
    public:
        const float x1;
        const float x2;
        const float y1;
        const float y2;
        const float z1;
        const float z2;
        const float phiMax;

        Hyperboloid(Transform* objectToWorld, Transform* worldToObject, Material* mat, Texture* tex, const float x1, const float x2, const float y1, const float y2, const float z1, const float z2, const float phiMax) : Object(objectToWorld, worldToObject, mat, tex), x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2), phiMax(phiMax) {};

        bool intersect(const Ray& r, Hit& res) const {
            Ray ray = (*worldToObject)(r);
            float ox = ray.origin.x;
            float oy = ray.origin.y;
            float oz = ray.origin.z;
            float dx = ray.direction.x;
            float dy = ray.direction.y;
            float dz = ray.direction.z;
            
            float a = dx*dx + dy*dy + dz*dz;
            float b = 2*(ox*dx + oz*dz - oy*dy);
            float c = ox*ox + oz*oz - oy*oy + 1;
            float D = b*b - 4*a*c;
            if(D < 0) return false;
            float t0 = (-b - std::sqrt(D))/(2*a);
            float t1 = (-b + std::sqrt(D))/(2*a);
            if(t0 > ray.tmax || t1 < ray.tmin) return false;
            float t = t0;
            Point3 hitPos = ray(t);
            float phi = std::atan2(hitPos.z, hitPos.x);
            if(phi < 0) phi += 2*M_PI;
            if(t < ray.tmin || hitPos.x < x1 || hitPos.x > x2 || hitPos.y < y1 || hitPos.y > y2 || hitPos.z < z1 || hitPos.z > z2 || phi > phiMax) {
                t = t1;
                hitPos = ray(t);
                phi = std::atan2(hitPos.z, hitPos.x);
                if(phi < 0) phi += 2*M_PI;
                if(t > ray.tmax || hitPos.x < x1 || hitPos.x > x2 || hitPos.y < y1 || hitPos.y > y2 || hitPos.z < z1 || hitPos.z > z2 || phi > phiMax) return false;
            }

            res.hitPos = hitPos;
            res.t = t;
            res.ray = ray;
            res.hitObj = const_cast<Hyperboloid*>(this);
            
            res.u = 1.0f - phi/phiMax;
            res.v = 0.0f;
            Vec3 dpdu = Vec3();
            Vec3 dpdv = Vec3();
            res.dpdu = dpdu;
            res.dpdv = dpdv;
            res.hitNormal = Vec3(0, 1, 0);

            res.inside = dot(ray.direction, res.hitNormal) > 0;
            if(res.inside)
                res.hitNormal = -res.hitNormal;

            res = (*objectToWorld)(res);
            return true;
        };
};
#endif
