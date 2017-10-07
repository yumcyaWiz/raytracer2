#ifndef RENDER_H
#define RENDER_H
#include <memory>
#include <omp.h>
#include "objects.h"
#include "camera.h"
#include "image.h"
#include "sky.h"
#include "sampler.h"
#include "timer.h"
class Render {
    public:
        Camera* cam;
        Objects* objs;
        Sky* sky;
        Image* img;
        int samples;


        Render(Camera* _cam, Objects* _objs, Sky* _sky, Image* _img, int _samples) {
            cam = _cam;
            objs = _objs;
            sky = _sky;
            img = _img;
            samples = _samples;
        };


        RGB Li(const Ray& ray, int depth) {
            if(depth > 10)
                return RGB(1.0f);

            Hit res;
            if(objs->intersect(ray, res)) {
                std::shared_ptr<Material> mat = res.hitObj->mat;
                std::shared_ptr<Texture> tex = res.hitObj->tex;

                Ray nextRay;
                float nextRay_pdf;
                if(mat->scatter(res, nextRay, nextRay_pdf))
                    return tex->get(res) * mat->brdf(res.hitPos, res.ray.direction, nextRay.direction)/nextRay_pdf * dot(-res.ray.direction, res.hitNormal) * Li(nextRay, depth + 1);
                else
                    return tex->get(res);
            }
            else {
                return sky->get(ray);
            }
        }
        void render() {
            Timer t;
            t.start();
            #pragma omp parallel for schedule(dynamic, 1)
            for(int k = 0; k < samples; k++) {
                for(int i = 0; i < img->height; i++) {
                    for(int j = 0; j < img->width; j++) {
                        float u = (2.0f*(i + rnd()) - img->height)/img->height;
                        float v = (2.0f*(j + rnd()) - img->width)/img->height;
                        Ray ray = cam->getRay(u, v);
                        img->set(i, j, img->get(i, j) + Li(ray, 0));
                    }
                }
                if(omp_get_thread_num() == 0)
                    std::cout << progressbar(k, samples) << " " << percentage(k, samples) << "\r" << std::flush; 
            }
            t.stop();
            img->divide(float(samples));
            img->gamma_correlation();
            img->ppm_output("output.ppm");
        };
};
#endif
