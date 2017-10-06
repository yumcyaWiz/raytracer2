#ifndef TEXTURE_H
#define TEXTURE_H
#include "rgb.h"
#include "hit.h"
#include <memory>
#include <cmath>
class Texture {
    public:
        virtual RGB get(const Hit& res) = 0;
};


class Mono : public Texture {
    public:
        RGB col;

        Mono(const RGB& _col) : col(_col) {};

        RGB get(const Hit& res) {
            return col;
        };
};


class TestTexture : public Texture {
    public:
        RGB get(const Hit& res) {
            return RGB(res.u, res.v, 0.0f);
        };
};


class Checkerboard : public Texture {
    public:
        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;
        float scale;

        Checkerboard(Texture* _odd, Texture* _even, float _scale) : odd(std::shared_ptr<Texture>(_odd)), even(std::shared_ptr<Texture>(_even)), scale(_scale) {};

        RGB get(const Hit& res) {
            float f = std::sin(res.hitPos.x/scale)*std::sin(res.hitPos.y/scale)*std::sin(res.hitPos.z/scale);
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
        float* img;

        ImageTexture(char* filename) {
        };

        RGB get(const Hit& res) {
            return RGB(1.0);
        };
};
#endif
