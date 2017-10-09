#ifndef TEXTURE_H
#define TEXTURE_H
#include "rgb.h"
#include "hit.h"
#include <memory>
#include <cmath>
#include <string>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
class Texture {
    public:
        virtual RGB get(const Hit& res) const = 0;
};


class Mono : public Texture {
    public:
        RGB col;

        Mono(const RGB& _col) : col(_col) {};

        RGB get(const Hit& res) const {
            return col;
        };
};


class TestTexture : public Texture {
    public:
        RGB get(const Hit& res) const {
            return RGB(res.u, res.v, 0.0f);
        };
};


class Checkerboard : public Texture {
    public:
        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;
        float scale;

        Checkerboard(Texture* _odd, Texture* _even, float _scale) : odd(std::shared_ptr<Texture>(_odd)), even(std::shared_ptr<Texture>(_even)), scale(_scale) {};

        RGB get(const Hit& res) const {
            float f = std::sin(res.u*scale*2.0*M_PI)*std::sin(res.v*scale*2.0*M_PI);
            if(f > 0)
                return odd->get(res);
            else
                return even->get(res);
        };
};


class ImageTexture : public Texture {
    public:
        int width;
        int height;
        unsigned char *img;

        ImageTexture(std::string filename) {
            int n;
            img = stbi_load(filename.c_str(), &width, &height, &n, 3);
        };
        ~ImageTexture() {
            stbi_image_free(img);
        };

        RGB get(const Hit& res) const {
            int w = (int)(res.u*width);
            int h = (int)((1.0 - res.v)*height);
            int adr = 3*w + 3*width*h;
            return RGB(img[adr]/255.0f, img[adr+1]/255.0f, img[adr+2]/255.0f);
        };
};
#endif
