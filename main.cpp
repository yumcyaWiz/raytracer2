#include <iostream>
#include "vec3.h"
#include "rgb.h"
#include "ray.h"
#include "image.h"
#include "camera.h"
#include "sampler.h"
#include "object.h"
#include "material.h"
#include "render.h"


int main() {
    Image img(512, 512);
    Render render(img);
    render.render();
    return 0;
}
