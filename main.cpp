#include <iostream>
#include "vec3.h"
#include "rgb.h"
#include "ray.h"
#include "image.h"


int main() {
    Image img(512, 512);
    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
            img.set(i, j, RGB(i, j, 255));
        }
    }
    img.ppm_output("output.ppm");
    return 0;
}
