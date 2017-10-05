#ifndef TEXTURE_H
#define TEXTURE_H
#include "rgb.h"
#include <memory>
#include <cmath>
class Texture {
    public:
        virtual RGB get(float u, float v) = 0;
};


class Mono : public Texture {
    public:
        RGB col;

        Mono(const RGB& _col) : col(_col) {};

        RGB get(float u, float v) {
            return col;
        };
};


class TextTexture : public Texture {
    public:
        RGB get(float u, float v) {
            return RGB(u, v, 0.0f);
        };
};


class Checkerboard : public Texture {
    public:
        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;
        float scale;


        Checkerboard(Texture* _odd, Texture* _even, float _scale) : odd(std::shared_ptr<Texture>(_odd)), even(std::shared_ptr<Texture>(_even)), scale(_scale) {};

        RGB get(float u, float v) {
            float f = std::sin(u/scale * 2.0f*M_PI)*std::sin(v/scale * 2.0f*M_PI);
            if(f > 0)
                return odd->get(u, v);
            else
                return even->get(u, v);
        };
};


class ImageTexture : public Texture {
    public:
        int width;
        int height;
        float* img;

        ImageTexture(char* filename) {
        };

        RGB get(float u, float v) {
            return RGB(1.0);
        };
};
#endif
