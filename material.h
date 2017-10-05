#ifndef MATERIAL_H
#define MATERIAL_H
#include <memory>
#include "rgb.h"
#include "hit.h"
#include "texture.h"
#include "sampler.h"
class Material {
    public:
        virtual bool scatter(const Hit& hit, Ray& nextRay, float& pdf) = 0;
        virtual float brdf(const Hit& hit) = 0;
};


class Diffuse : public Material {
    public:
        float reflectivity;

        Diffuse(float _r) : reflectivity(_r) {};

        bool scatter(const Hit& res, Ray& nextRay, float& pdf) {
            nextRay = Ray(res.hitPos, random_in_unitSphere());
            pdf = 1.0f;
        };
        float brdf(const Hit& hit) {
            float cos_term = 1.0f;
            return reflectivity/cos_term; 
        };
};
class Mirror : Material {
};
class Glass : Material {
};
#endif
