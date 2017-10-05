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
        int samples;


        Render(const Camera& _cam, const Objects& _objs, Sky* _sky, Image& _img, int _samples) : cam(_cam), objs(_objs), sky(std::shared_ptr<Sky>(_sky)), img(&_img), samples(_samples) {};


        RGB Li(const Ray& ray, int depth) {
            if(depth > 10)
                return RGB(1.0);

            Hit res;
            if(objs.intersect(ray, res)) {
                std::shared_ptr<Material> mat = res.hitObj->mat;
                std::shared_ptr<Texture> tex = res.hitObj->tex;

                Ray nextRay;
                float nextRay_pdf;
                if(mat->scatter(res, nextRay, nextRay_pdf))
                    return tex->get(res.u, res.v) * mat->brdf(res.hitPos, res.ray.direction, nextRay.direction)/nextRay_pdf * Li(nextRay, depth + 1);
                else
                    return tex->get(res.u, res.v);
            }
            else {
                return sky->get(ray);
            }
        }
        void render() {
            for(int k = 0; k < samples; k++) {
                for(int i = 0; i < img->height; i++) {
                    for(int j = 0; j < img->width; j++) {
                        float u = (2.0f*i - img->height)/img->height;
                        float v = (2.0f*j - img->width)/img->height;
                        Ray ray = cam.getRay(u, v);
                        img->set(i, j, img->get(i, j) + Li(ray, 0));
                    }
                }
            }
            img->divide(float(samples));
            img->ppm_output("output.ppm");
        };
};
#endif
