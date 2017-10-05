#ifndef MATERIAL_H
#define MATERIAL_H
#include "rgb.h"
class Material {
    public:
        virtual bool scatter(const Hit& hit, Ray& nextRay, float& pdf) = 0;
        virtual RGB brdf(const Hit& hit) = 0;
};


class Diffuse : Material {
    public:
        RGB reflectivity;
        

        Diffuse(const RGB& _r) : reflectivity(_r) {};
        

        bool scatter(const Hit& res, Ray& nextRay, float& pdf) {
            nextRay = Ray(res.hitPos, random_in_unitSphere());
            pdf = 1.0f;
        };
        RGB brdf(const Hit& hit) {
            float cos_term = 1.0;
            return reflectivity/cos_term; 
        };
};
class Mirror : Material {
};
class Glass : Material {
};
#endif
