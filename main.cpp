#include <iostream>
#include "vec3.h"
#include "rgb.h"
#include "ray.h"
#include "image.h"
#include "camera.h"
#include "sampler.h"
#include "object.h"


int main() {
    Image img(512, 512);
    Camera cam(Vec3(0, 0, -5), Vec3(0, 0, 1));
    Sphere sphere(Vec3(0, 0, 0), 1.0);
    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
            float u = (2.0*i - img.width)/img.height;
            float v = (2.0*j - img.height)/img.height;
            Ray ray = cam.getRay(u, v);
            Hit res;
            if(sphere.intersect(ray, res)) {
                RGB col = RGB((res.hitNormal + 1.f)/2.f);
                img.set(i, j, col);
            }
            else {
                img.set(i, j, RGB(0));
            }
        }
    }
    img.ppm_output("output.ppm");
    return 0;
}
