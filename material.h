#ifndef MATERIAL_H
#define MATERIAL_H
class Material {
    public:
        virtual bool scatter(const Hit& hit, Ray& scattered_ray) = 0;
        virtual float brdf(const Hit& hit) = 0;
};


class Diffuse : Material {
    public:
        float reflectivity;
};
class Mirror : Material {
};
class Glass : Material {
};
#endif
