#ifndef TEXTURE_H
#define TEXTURE_H
#include "rgb.h"
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


class Checkerboard : public Texture {
    public:
        Checkerboard() {};

        RGB get(float u, float v) {
        };
};
#endif
