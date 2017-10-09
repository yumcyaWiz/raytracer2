#ifndef SKY_H
#define SKY_H
class Sky {
    public:
        virtual RGB get(const Ray& ray) const = 0;

        Sky() {};
};


class testSky : public Sky {
    public:
        RGB col;

        testSky(const RGB& _col) : col(_col) {};

        RGB get(const Ray& ray) const {
            return col;
        };
};


class simpleSky : public Sky {
    public:
        float intensity;

        simpleSky(float i) : intensity(i) {};

        RGB get(const Ray& ray) const {
            float t = (ray.direction.y + 1.0f)*0.5f;
            return intensity * ((1.0f - t)*RGB(1.0f) + t*RGB(0.5, 0.7, 1.0));
        };
};
#endif
