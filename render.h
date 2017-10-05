#ifndef RENDER_H
#define RENDER_H
#include <memory>
#include "objects.h"
#include "camera.h"
#include "image.h"
#include "sky.h"
class Render {
    public:
        Camera cam;
        Objects objs;
        std::shared_ptr<Sky> sky;
        Image *img;


        Render(const Camera& _cam, const Objects& _objs, Sky* _sky, Image& _img) : cam(_cam), objs(_objs), sky(std::shared_ptr<Sky>(_sky)), img(&_img) {};


        RGB Li(const Ray& ray) {
            Hit res;
            if(objs.intersect(ray, res)) {
                return RGB(1.0);
            }
            else {
                return sky->get(ray);
            }
        }
        void render() {
            for(int i = 0; i < img->width; i++) {
                for(int j = 0; j < img->height; j++) {
                    float u = (2.0f*i - img->width)/img->height;
                    float v = (2.0f*j - img->height)/img->height;
                    Ray ray = cam.getRay(u, v);
                    img->set(i, j, Li(ray));
                }
            }
            img->ppm_output("output.ppm");
        };
};
#endif
