#ifndef SKY_H
#define SKY_H

#include <string>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
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


class IBL : public Sky {
    public:
        int width;
        int height;
        float *HDRI;

        IBL(std::string filename) {
            int n;
            HDRI = stbi_loadf(filename.c_str(), &width, &height, &n, 0);
        };
        ~IBL() {
            stbi_image_free(HDRI);
        };

        RGB get(const Ray& ray) const {
            float phi = std::atan2(ray.direction.z, ray.direction.x);
            if(phi < 0) phi += 2*M_PI;
            double theta = std::acos(ray.direction.y);

            float u = phi/(2.0*M_PI);
            float v = theta/M_PI;

            int w = (int)(u*width);
            int h = (int)(v*height);
            int adr = 3*w + 3*width*h;
            return RGB(HDRI[adr], HDRI[adr+1], HDRI[adr+2]);
        };
};
#endif
