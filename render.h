#ifndef RENDER_H
#define RENDER_H
#include <memory>
#include "objects.h"
class Render {
    public:
        Image *img;
        Objects objs;


        Render(Image& _img) : img(&_img) {};


        void render() {
            Camera cam(Vec3(0, 0, 0), Vec3(0, 0, 1));
            objs.add(new Sphere(Vec3(0, -10001.0f, 0), 10000.0f));
            objs.add(new Sphere(Vec3(0, 0, 3), 1.0f));

            for(int i = 0; i < img->width; i++) {
                for(int j = 0; j < img->height; j++) {
                    float u = (2.0f*i - img->width)/img->height;
                    float v = (2.0f*j - img->height)/img->height;
                    Ray ray = cam.getRay(u, v);
                    Hit res;
                    if(objs.intersect(ray, res)) {
                        RGB mat = RGB((res.hitNormal + 1.0)/2.0);
                        img->set(i, j, mat);
                    }
                    else {
                        img->set(i, j, RGB(0));
                    }
                }
            }
            img->ppm_output("output.ppm");
        };
};
#endif
