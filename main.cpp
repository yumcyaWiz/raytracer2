#include <iostream>
#include "vec3.h"
#include "rgb.h"
#include "ray.h"
#include "image.h"
#include "sampler.h"
#include "object.h"


int main() {
    Image img(512, 512);
    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
            img.set(i, j, RGB(255*rnd(), 255*rnd(), 255*rnd()));
        }
    }
    img.ppm_output("output.ppm");
    return 0;
}
