#ifndef MATERIAL_H
#define MATERIAL_H
#include <memory>
#include "vec3.h"
#include "rgb.h"
#include "hit.h"
#include "texture.h"
#include "sampler.h"
class Material {
    public:
        virtual bool scatter(const Hit& hit, Ray& nextRay, float& pdf) const = 0;
        virtual float brdf(const Vec3& hitPos, const Vec3& ray_in, const Vec3& ray_out) const = 0;
};


class Diffuse : public Material {
    public:
        float reflectivity;

        Diffuse(float _r) : reflectivity(_r) {};

        bool scatter(const Hit& res, Ray& nextRay, float& pdf) const {
            nextRay = Ray(res.hitPos, normalize(res.hitNormal + random_in_unitSphere())); 
            pdf = dot(-res.ray.direction, res.hitNormal)/M_PI;
            return true;
        };
        float brdf(const Vec3& hitPos, const Vec3& ray_in, const Vec3& ray_out) const {
            return reflectivity/M_PI;
        };
};


class Mirror : public Material {
    public:
        float reflectivity;

        Mirror(float _r) : reflectivity(_r) {};

        bool scatter(const Hit& res, Ray& nextRay, float& pdf) const {
            nextRay = Ray(res.hitPos, reflect(res.ray.direction, res.hitNormal));
            pdf = dot(-res.ray.direction, res.hitNormal);
            return true;
        };
        float brdf(const Vec3& hitPos, const Vec3& ray_in, const Vec3& ray_out) const {
            return reflectivity;
        };
};


inline float fresnel(float n1, float n2, const Vec3& v, const Vec3& n) {
    float f0 = std::pow((n1 - n2)/(n1 + n2), 2.0);
    return f0 + (1.0 - f0)*std::pow(1.0 - dot(-v, n), 5.0);
}
class Glass : public Material {
    public:
        float IOR;

        Glass(float _IOR) : IOR(_IOR) {};

        bool scatter(const Hit& res, Ray& nextRay, float& pdf) const {
            pdf = dot(-res.ray.direction, res.hitNormal);
            if(!res.inside) {
                float fr = fresnel(1.0f, IOR, res.ray.direction, res.hitNormal);
                if(rnd() < fr) {
                    nextRay = Ray(res.hitPos, reflect(res.ray.direction, res.hitNormal));
                    return true;
                }
                else {
                    Vec3 dir;
                    if(refract(res.ray.direction, res.hitNormal, 1.0f, IOR, dir)) {
                        nextRay = Ray(res.hitPos, dir);
                        return true;
                    }
                    else {
                        nextRay = Ray(res.hitPos, reflect(res.ray.direction, res.hitNormal));
                        return true;
                    }
                }
            }
            else {
                float fr = fresnel(IOR, 1.0f, res.ray.direction, res.hitNormal);
                if(rnd() < fr) {
                    nextRay = Ray(res.hitPos, reflect(res.ray.direction, res.hitNormal));
                    return true;
                }
                else {
                    Vec3 dir;
                    if(refract(res.ray.direction, res.hitNormal, IOR, 1.0f, dir)) {
                        nextRay = Ray(res.hitPos, dir);
                        return true;
                    }
                    else {
                        nextRay = Ray(res.hitPos, reflect(res.ray.direction, res.hitNormal));
                        return true;
                    }
                }
            }
        };
        float brdf(const Vec3& hitPos, const Vec3& ray_in, const Vec3& ray_out) const {
            return 1.0f;
        };
};


class Emissive : public Material {
};
#endif
