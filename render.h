#ifndef RENDER_H
#define RENDER_H
#include <memory>
#include <cstdlib>
#include <string>
#include <cmath>
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
        const int maxDepth = 100;
        float russian_roulette_prob = 1.0;


        Render(Camera* _cam, Objects* _objs, Sky* _sky, Image* _img, int _samples) {
            cam = _cam;
            objs = _objs;
            sky = _sky;
            img = _img;
            samples = _samples;
        };


        RGB Li(const Ray& ray, int depth) {
            if(depth < 10) {
                russian_roulette_prob = 1.0;
            }
            else {
                russian_roulette_prob /= 1.1;
            }
            if(rnd() > russian_roulette_prob || depth >= maxDepth) {
                return RGB(1.0f);
            }

            Hit res;
            if(objs->intersect(ray, res)) {
                const Material* mat = res.hitObj->mat;
                const Texture* tex = res.hitObj->tex;

                Ray nextRay;
                float nextRay_pdf;
                if(mat->scatter(res, nextRay, nextRay_pdf)) {
                    float k = mat->brdf(res.hitPos, res.ray.direction, nextRay.direction) * dot(nextRay.direction, res.hitNormal)/(nextRay_pdf * russian_roulette_prob);
                    if(std::isnan(k))
                        k = 1.0f;
                    return tex->get(res) * k * Li(nextRay, depth + 1);
                }
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
                        float w;
                        Ray ray = cam->getRay(u, v, w);
                        img->set(i, j, img->get(i, j) + w*Li(ray, 0));
                    }
                }
                if(omp_get_thread_num() == 0)
                    std::cout << progressbar(k, samples) << " " << percentage(k, samples) << "\r" << std::flush; 
            }
            t.stop();
        };
        void render_normal() {
            for(int i = 0; i < img->height; i++) {
                for(int j = 0; j < img->width; j++) {
                    float u = (2.0*i - img->height)/img->height;
                    float v = (2.0*j - img->width)/img->width;
                    float w;
                    Ray ray = cam->getRay(u, v, w);
                    Hit res;
                    if(objs->intersect(ray, res)) {
                        img->set(i, j, RGB(res.hitNormal + 1.0)/2.0);
                    }
                    else {
                        img->set(i, j, RGB(0));
                    }
                }
            }
        }

        void output() {
            img->divide(float(samples));
            img->gamma_correlation();
            img->ppm_output("output.ppm");
        };
        void png_output() {
            img->divide(float(samples));
            img->gamma_correlation();
            img->ppm_output("output.ppm");
            std::string command = "convert output.ppm " + ctime_string() + ".png";
            std::system(command.c_str());
        };
};
#endif
